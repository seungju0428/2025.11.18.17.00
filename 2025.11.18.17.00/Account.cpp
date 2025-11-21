#include "Account.h"
#include <string>
using namespace std;

Account::Account(const string& bank, const string& user, const string& accNum, int bal, const string& cardNum, const string& cardPw, const string& transactionHistory)
	: bankName(bank), userName(user), accountNumber(accNum), balance(bal), cardNumber(cardNum), cardPassword(cardPw), transactionHistories(transactionHistory) {} // »ý¼ºÀÚ

bool Account::addFunds(long amount) {
    if (amount <= 0) {
        return false;  //실패,
    }
    m_balance += amount;
    return true;
}

bool Account::deductFunds(long amount) {
    if (amount <= 0 || amount % 1000 != 0) { // 출금 금액은 1000원 단위
        return false;
    }
    if (m_balance >= amount) {
        m_balance -= amount;
        return true;
    }
    return false; //잔액 부족
}
