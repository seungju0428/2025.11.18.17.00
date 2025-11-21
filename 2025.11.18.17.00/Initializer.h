#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "Bank.h"
#include "ATM.h"
#include "Interface.h"
using namespace std;

class Initializer {
private:
    // map<string, Bank*> allBanks; // key: 은행 이름
    vector<ATM*> allATMs; // element: ATM pointer
    Interface& ui;
public:
    void run();
    map<string, Bank*>& getAllBanks() { return allBank; }
    Initializer(ifstream& fin, Interface& uiInput); // 생성자
    ATM* findATMBySerialNumber(string serialNumberInput);
    Bank* findBankByCardNumber(string cardNumberInput); // ATM에서 사용
    Account* findAccountPtrByCardNumber(string cardNumberInput);
};

#endif
