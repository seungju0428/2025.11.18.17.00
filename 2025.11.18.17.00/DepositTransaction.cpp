
#include "DepositTransaction.h"
#include "Session.h"
#include "ATM.h"     // CashDenominations 구조체 및 ATM 함수 사용
#include "Account.h" // Account 함수 사용
#include "Interface.h" // Interface 함수 사용
#include <iostream>


using namespace std;



DepositTransaction::DepositTransaction(Session* session) : Transaction(session) {}

// 현금 입금
void DepositTransaction::processCashDeposit(long fee) {
    Interface& ui = pSession->getUI();
    Account* account = pSession->getAccount();
    ATM* atm = pSession->getATM();

    // Interface& 를 사용하여 입력 받기
    int cnt50k = ui.inputInt("Input50kCount");
    int cnt10k = ui.inputInt("Input10kCount");
    int cnt5k  = ui.inputInt("Input5kCount");
    int cnt1k  = ui.inputInt("Input1kCount");

    int totalBills = cnt50k + cnt10k + cnt5k + cnt1k;

    // [REQ 4.2] 최대 매수 제한
    if (totalBills > 50) { ui.displayErrorMessage("ExceedCashLimit"); return; }
    if (totalBills == 0) { ui.displayErrorMessage("NoCashInserted"); return; }

    long depositAmount = (long)cnt50k * 50000 + (long)cnt10k * 10000 + 
                         (long)cnt5k * 5000 + (long)cnt1k * 1000;

    CashDenominations feeCash = {0, 0, 0, 0};
    if (!collectFee(fee, feeCash)) { return; }

    CashDenominations depositCash = {cnt50k, cnt10k, cnt5k, cnt1k};
    CashDenominations totalToATM;
    totalToATM.c50k = depositCash.c50k + feeCash.c50k;
    totalToATM.c10k = depositCash.c10k + feeCash.c10k;
    totalToATM.c5k  = depositCash.c5k  + feeCash.c5k;
    totalToATM.c1k  = depositCash.c1k  + feeCash.c1k;

    // [REQ 4.5] ATM 시재 증가
    atm->addCashToATM(totalToATM);

    // [REQ 4.3] 계좌 잔액 증가
    if (account->addFunds(depositAmount)) {
        string summaryLog = "[TxID: " + to_string(transactionID) + "] " + 
                            to_string(depositAmount) + "KRW deposited (Fee: " + to_string(fee) + ")";
        pSession->recordTransaction(summaryLog); // Session에 기록 함수 필요
        
        ui.displayMessage("DepositSuccess");
        
				ui.displayMessage("DepositAmountLabel"); 
        cout << depositAmount;
        ui.displayMessage("WonUnit"); 
        cout << endl;

        ui.displayMessage("FeeLabel");
        cout << fee;
        ui.displayMessage("WonUnit");
        cout << endl;
    } else {
        ui.displayErrorMessage("DepositFailed");
    }
}


// 수표 입금
void DepositTransaction::processCheckDeposit(long fee) {
    Interface& ui = pSession->getUI();
    Account* account = pSession->getAccount();
    ATM* atm = pSession->getATM();
    
    long totalCheckAmount = 0;
    int totalCheckCount = 0;

    ui.displayMessage("StartCheckDepositInfo");

    while (true) {
        // 수표 금액 입력 (Interface에 inputCheckAmount가 있다고 가정)
        long amount = ui.inputCheckAmount("PromptCheckAmountLoop"); 
        if (amount == 0) break;
        if (amount < 100000) { ui.displayErrorMessage("InvalidCheckAmount"); continue; }
        
        int count = ui.inputInt("PromptCheckCount");
        if (count <= 0) { ui.displayErrorMessage("InvalidInput_Negative"); continue; }
        
        totalCheckAmount += (amount * count);
        totalCheckCount += count;
        
        // 중간 집계 출력 
        ui.totalCheckInfo((int)totalCheckAmount, totalCheckCount);
    }
    

    if (totalCheckCount == 0) { ui.displayErrorMessage("NoCheckInputExit"); return; }
    if (totalCheckCount > 30) { ui.displayErrorMessage("ExceedCheckLimit"); return; }

		cout << "---------------------------------" << endl;
    ui.displayMessage("FinalCheckTotalAmount");
    cout << totalCheckAmount;
    ui.displayMessage("WonUnit");
    cout << endl;

    ui.displayMessage("FinalCheckTotalCount");
    cout << totalCheckCount;
    ui.displayMessage("SheetUnit");
    cout << endl;

    ui.displayMessage("FinalCheckDepositConfirm");
    cout << "---------------------------------" << endl;

    CashDenominations feeCash = {0, 0, 0, 0};
    if (!collectFee(fee, feeCash)) { return; }
    
    // [REQ 4.6] 수표는 ATM 시재(사용가능 현금)를 증가시키지 않음. 수수료(현금)만 추가.
    atm->addCashToATM(feeCash);

    if (account->addFunds(totalCheckAmount)) {
        string summaryLog = "[TxID: " + to_string(transactionID) + "] " +
                            to_string(totalCheckAmount) + "KRW (Check) deposited (Fee: " + to_string(fee) + ")";
        pSession->recordTransaction(summaryLog);
  
	  		ui.displayMessage("CheckDepositSuccess");
        
        ui.displayMessage("TotalDepositAmountLabel");
        cout << totalCheckAmount;
        ui.displayMessage("WonUnit");
        cout << endl;
    } else {
        ui.displayErrorMessage("DepositFailed");
    }
}


void DepositTransaction::run() {
    Interface& ui = pSession->getUI();
    // 입금 유형 선택 (1: 현금, 2: 수표) - inputInt로 처리한다고 가정
    int depositType = ui.inputInt("AskDepositType"); 
    
    if (depositType != 1 && depositType != 2) return;

    long fee = calculateFee("Deposit");

    if (depositType == 1) {
        processCashDeposit(fee);
    } else {
        processCheckDeposit(fee);
    }
}
