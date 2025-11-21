#include "Transaction.h"
#include "Session.h"
#include "Account.h"
#include "ATM.h"
#include "Interface.h"
#include <iostream>

// 초기화
int Transaction::nextID = 1;

Transaction::Transaction(Session* session) : pSession(session) {
    transactionID = nextID++;
}

int Transaction::getTransactionID() const {
    return transactionID;
}



long Transaction::calculateFee(const string& transactionType, const string& destBankName) const {
    Bank* userBankPtr = pSession->getBank();
    ATM* atm = pSession->getATM();

    const string userBank  = userBankPtr->getPrimaryBank(); 
    const string atmBank   = atm->getPrimaryBank();         
    const string destBank  = destBankName; // Transfer 에서 넘겨주는 은행 이름

    bool isUserPrimary = (userBank == atmBank);
    bool isDestPrimary = (!destBank.empty() && destBank == atmBank);

    if (transactionType == "Deposit") {
        return isUserPrimary ? 0 : 1000;
    }
    else if (transactionType == "Withdrawal") {
        return isUserPrimary ? 1000 : 2000;
    }
    else if (transactionType == "CashTransfer") {
        return 2000;
    }
    else if (transactionType == "Transfer") {
        if (destBank.empty()) return -1; 

        if (userBank == destBank) {
            return 1000;
        } else if (isUserPrimary && isDestPrimary) {
            return 1000;
        } else if (isUserPrimary != isDestPrimary) {
            return 2000;
        } else {
            return 4000;
        }
    }
    return -1;
}


bool Transaction::collectFee(long fee, CashDenominations& outFeeCash) {
    if (fee <= 0) return true;

    Interface& ui = pSession->getUI();

    // "수수료 [fee]원이 필요합니다."
		ui.displayMessage("FeeNoticePart1");
    cout << fee;
    ui.displayMessage("FeeNoticePart2");
    cout << endl;

    int feeBillsRequired = fee / 1000;
    // "1000원권 [n]장을 넣어주세요"
    ui.displayMessage("FeePromptPart1"); 
    cout << feeBillsRequired;
    ui.displayMessage("FeePromptPart2");

    int feeBillsInserted = ui.inputInt("Input1kCount");

    if (feeBillsInserted < feeBillsRequired) {
        ui.displayMessage("InsufficientFee"); // 에러 
        return false;
    }

    outFeeCash.c1k = feeBillsInserted; // 수수료는 1000원권으로만 처리한다고 가정
    return true;
}
