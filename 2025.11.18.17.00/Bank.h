#ifndef BANK_H
#define BANK_H
#include <string>
#include <map>
#include "Account.h"
using namespace std;

class Bank {
private:
    string bankName;
    map<string, Account*> accounts; // key: °èÁÂ¹øÈ£

public:    
    Bank(const string& name);
    void addAccount(Account*);
    string getPrimaryBank() const { return bankName; }
    Bank* getBankByCardNumber(string cardNumberInput);
    Account* getAccountPtrByCardNumber(string cardNumberInput);
    bool isCorrectCardPW(Account* pAccount, string cardPWInput);

    Account* findAccount(string accountNumber);
};

#endif
