#include "TransferTransaction.h"
#include "Session.h"
#include "ATM.h"
#include "Account.h"
#include "Interface.h"
#include "Bank.h"
#include <iostream>
#include <map>

using namespace std;

TransferTransaction::TransferTransaction(Session* session) : Transaction(session) {}

// 솔직히 여기 어떻게 구현해야할지 모르겠음
// 이체할 계좌 찾기
Account* TransferTransaction::findDestinationAccount(const string& destAccNum) {
    map<string, Bank*>& allBanks = pSession->getAllBanks();
    for (auto const& [bankName, bankPtr] : allBanks) {
        Account* found = bankPtr->findAccount(destAccNum);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

// 현금 이체
void TransferTransaction::processCashTransfer(long fee, Account* destAccount) {
    Interface& ui = pSession->getUI();
    ATM* atm = pSession->getATM();

    ui.displayMessage("CashTransferInputGuide");

    int cnt50k = ui.inputInt("Input50kCount");
    int cnt10k = ui.inputInt("Input10kCount");
    int cnt5k  = ui.inputInt("Input5kCount");
    int cnt1k  = ui.inputInt("Input1kCount");

    int totalBills = cnt50k + cnt10k + cnt5k + cnt1k;

    if (totalBills > 50) { ui.displayErrorMessage("ExceedCashLimit"); return; }
    if (totalBills == 0) { ui.displayMessage("TransactionCancelled"); return; }

    long transferAmount = (long)cnt50k * 50000 + (long)cnt10k * 10000 + 
                          (long)cnt5k * 5000 + (long)cnt1k * 1000;

    CashDenominations feeCash = {0, 0, 0, 0};
    if (!collectFee(fee, feeCash)) { return; }

    CashDenominations transferCash = {cnt50k, cnt10k, cnt5k, cnt1k};
    CashDenominations totalToATM;
    totalToATM.c50k = transferCash.c50k + feeCash.c50k;
    totalToATM.c10k = transferCash.c10k + feeCash.c10k;
    totalToATM.c5k  = transferCash.c5k  + feeCash.c5k;
    totalToATM.c1k  = transferCash.c1k  + feeCash.c1k;

    // 현금 송금 시 투입된 현금은 ATM 사용가능 자금으로 추가됨
    atm->addCashToATM(totalToATM);

    // 송금 성공 반영
    if (destAccount->addFunds(transferAmount)) {
        string summary = "[TxID: " + to_string(transactionID) + "] " +
                         to_string(transferAmount) + "KRW Cash Transferred to " + destAccount->getAccountNumber() + " (Fee: " + to_string(fee) + ")";
        pSession->recordTransaction(summary);
        ui.displayMessage("TransferSuccess");
        
	// 아직 구분
        ui.displayMessage("TransferAmountLabel");
        cout << transferAmount;
        ui.displayMessage("WonUnit");
        cout << endl;

        ui.displayMessage("FeeLabel");
        cout << fee;
        ui.displayMessage("WonUnit");
        cout << endl;

        ui.displayMessage("ReceiverLabel");
        cout << destAccount->getUserName() << endl;
    } else {
        ui.displayErrorMessage("TransactionFailed");
    }
    // ui ->wait() 이 원래 있었음
}

// 계좌 이체
void TransferTransaction::processAccountTransfer(long fee, Account* destAccount) {
    Interface& ui = pSession->getUI();
    Account* account = pSession->getAccount();

    long amount = ui.inputInt("TransferAmountPrompt");

    if (amount == 0) { ui.displayMessage("TransactionCancelled"); return; }

    long totalDeduction = amount + fee;
    if (account->getBalance() < totalDeduction) {
        ui.displayErrorMessage("InsufficientBalance"); return;
    }

    // 내 계좌 차감 -> 상대 계좌 입금
    if (account->deductFunds(totalDeduction)) {
        destAccount->addFunds(amount);

        string summary = "[TxID: " + to_string(transactionID) + "] " +
                         to_string(amount) + "KRW Account Transferred to " + destAccount->getAccountNumber() + " (Fee: " + to_string(fee) + ")";
        pSession->recordTransaction(summary);

        ui.displayMessage("TransferSuccess");
        
        ui.displayMessage("TransferAmountLabel");
        cout << amount;
        ui.displayMessage("WonUnit");
        cout << endl;

        ui.displayMessage("FeeLabel");
        cout << fee;
        ui.displayMessage("WonUnit");
        cout << endl;

        ui.displayMessage("BalanceAfterTransaction");
        cout << account->getBalance();
        ui.displayMessage("WonUnit");
        cout << endl;
    } else {
        ui.displayErrorMessage("TransactionFailed");
    }
   // ui->wait 있음
}

void TransferTransaction::run() {
    Interface& ui = pSession->getUI(); 
    Account* account = pSession->getAccount();

    while (true) {
        // 1. 이체 옵션 선택
        int choice = ui.inputInt("TransferOptionMenu"); 
        
        if (choice == 0) { 
            ui.displayMessage("TransactionCancelled");
            // ui.wait(); // 
            return; // 취소 시 함수 종료
        }
        
        // 잘못된 입력 시 continue를 통해 재시도
        if (choice != 1 && choice != 2) { 
            ui.displayMessage("InvalidMenuChoice"); 
            // ui.wait(); 
            continue; 
        }

        // 2. 계좌번호 입력
        ui.displayMessage("AccountNumPrompt");
        string destAccNum; 
        cin >> destAccNum; // 또는 ui.inputString()

        if (destAccNum == "0") { 
            ui.displayMessage("TransactionCancelled");
            return; 
        }

        // 자가 이체 방지
        if (choice == 2 && destAccNum == account->getAccountNumber()) {
             ui.displayMessage("TransferToSelfError"); 
             continue; // 다시 입력 받기 위해 루프 처음으로
        }

        // 목적 계좌 확인
        Account* destAccount = findDestinationAccount(destAccNum);
        if (destAccount == nullptr) {
            ui.displayMessage("InvalidAccount"); 
            continue; // 다시 입력 받기 위해 루프 처음으로
        }

        // 3. 실제 이체 진행
        if (choice == 1) {
            // 현금 송금 (타행 여부와 관계없이 수수료 고정)
            long fee = calculateFee("CashTransfer", "");
            processCashTransfer(fee, destAccount);
        } else {
            // 계좌 이체 (상대 은행 이름 필요 -> 수수료 계산에 사용)
            long fee = calculateFee("Transfer", destAccount->getBankName());
            processAccountTransfer(fee, destAccount);
        }
        
        // 거래가 정상적으로 시도되었으면 루프 나감
        break; 
    }
}
