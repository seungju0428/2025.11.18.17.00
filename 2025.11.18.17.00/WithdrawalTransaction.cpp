
#include "WithdrawalTransaction.h"
#include "Session.h"
#include "ATM.h"
#include "Account.h"
#include "Interface.h"
#include <iostream>

using namespace std;

WithdrawalTransaction::WithdrawalTransaction(Session* session) : Transaction(session) {}


bool WithdrawalTransaction::processSingleWithdrawal() {
    Interface& ui = pSession->getUI();
    Account* account = pSession->getAccount();
    ATM* atm = pSession->getATM();

    // 잔액 확인
    ui.displayMessage("CurrentBalance");
    cout << account->getBalance();
    ui.displayMessage("WonUnit");
    cout << endl;

    long amount = ui.inputInt("WithdrawalAmountPrompt"); // 출금액 입력

    if (amount == 0) { 
        ui.displayMessage("TransactionCancelled"); 
        return false; 
    }
    // 1회 최대 50만원
    if (amount > 500000) { 
        ui.displayErrorMessage("ExceedWithdrawalLimit"); 
        return false; 
    }
    if (amount % 1000 != 0) { 
        ui.displayErrorMessage("InvalidAmountUnit"); 
        return false; 
    }

    long fee = calculateFee("Withdrawal");
    long totalDeduction = amount + fee;

    // 잔액 및 ATM 시재 확인
    if (account->getBalance() < totalDeduction) {
        ui.displayErrorMessage("InsufficientBalance"); 
        return false;
    }
    
    // ATM에서 출금 가능한지 확인 
    if (!atm->dispenseCash(amount)) {
        ui.displayErrorMessage("InsufficientATMCash"); 
        return false;
    }

    // 계좌 차감
    if (account->deductFunds(totalDeduction)) {
        string summaryLog = "[TxID: " + to_string(transactionID) + "] " +
                            to_string(amount) + "KRW withdrawn (Fee: " + to_string(fee) + ")";
        pSession->recordTransaction(summaryLog);
        
        ui.displayMessage("WithdrawalSuccess");
        
        // 변경하기
        ui.displayMessage("WithdrawalAmountLabel");
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
        
        return true;
    } else {
        ui.displayMessage("TransactionFailed"); return false;
    }
}


void WithdrawalTransaction::run() {
    Interface& ui = pSession->getUI();
    
    // [REQ 5.6] 세션 당 최대 3회 출금 제한
    if (pSession->getWithdrawalCount() >= 3) {
        ui.displayErrorMessage("MaxWithdrawalLimitReached");
        ui.displayMessage("ReturningToMenu");
        // ui.wait();
        return;
    }

    while (pSession->getWithdrawalCount() < 3) {
        bool success = processSingleWithdrawal();

        if (success) {
            pSession->increaseWithdrawalCount();
        } else {
            break; // 실패 시 중단
        }

        if (pSession->getWithdrawalCount() < 3) {
            int choice = ui.inputInt("AskAdditionalWithdrawal");
            if (choice != 1) {
                ui.displayMessage("ReturningToMenu");
                // ui.wait();
                return;
            }
        } else {
            ui.displayErrorMessage("MaxWithdrawalLimitReached");
            ui.displayMessage("ReturningToMenu"); 
            // ui.wait();
            return;
        }
    }
}
