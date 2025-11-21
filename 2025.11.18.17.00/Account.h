#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using namespace std;

class Account {
private:
    string bankName;
    string userName;
    string accountNumber;
    int balance;
    string cardNumber;
    string cardPassword;
    string transactionHistories; // 거래 내역 어떤 구조로 저장할지 고민 필요

public:
    Account(const string& bank, const string& user, const string& accNum, int bal, const string& cardNum, const string& cardPw, const string& transactionHistory); // 생성자
    string getAccountNumber() { return accountNumber; }
    string getCardNumber() { return cardNumber; }
    string getCardPassword() { return cardPassword; }

    string getBankName() const { return bankName; }
    string getUserName() const { return userName; }
    int getBalance() const { return balance; }
    
    bool addFunds(long amount);                        // 입금
    bool deductFunds(long amount);                       // 출금
};

#endif
