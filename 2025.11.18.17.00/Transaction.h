#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "ATM.h" // CashDenominations 구조체 사용

using namespace std;

class Session; // 전방 선언

class Transaction {
protected:
    Session* pSession;      // child class들이 사용할 Session pointer
    int transactionID;      // 고유 거래 ID
    static int nextID;      // ID 생성을 위한 정적 변수

public:
    Transaction(Session* session);
    virtual ~Transaction() {}

    virtual void run() = 0;

    // 공통 기능
    int getTransactionID() const;
    long calculateFee(const string& transactionType, const string& destBankName = "") const;
    bool collectFee(long fee, CashDenominations& outFeeCash);
};

#endif
