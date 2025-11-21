#ifndef ATM_H
#define ATM_H
#include <string>
#include <algorithm>
class Initializer; // inlcude 문제로 전방 선언
#include "Bank.h"
#include "Interface.h"
using namespace std;

// 돈 구조
struct CashDenominations {
    int c50k = 0;
    int c10k = 0;
    int c5k = 0;
    int c1k = 0;
};

class ATM {
private:    
    Bank* pPrimaryBank;
    string serialNumber;
    string type;
    string languageMode;

    CashDenominations availableCash; // 돈 파트 수정 완료

    string adminCardNumber; // 0000-0000-0000 (고객의 카드 번호랑 아예 다른 구조로 만드는 게 안전하려나? ex. 00-00-00)
    string atmTransactionHistory;
    int index; // 세션 기록 관련된 부분에서 쓰려나?
    Initializer* pInit;
    Interface& ui;
public:
    void run();

    ATM(Bank* primaryBank, const string& serial, const string& t, const string& lang, int cash50k, int cash10k, int cash5k, int cash1k, Initializer* initializer, Interface& uiInput);
    string getPrimaryBank() const { return pPrimaryBank->getPrimaryBank(); } // return getPrimaryBank()는?
    string getSerialNumber() const { return serialNumber; }
    string getType() const { return type; }
    string getLanguageMode() const { return languageMode; }
    string getATMTransactionHistory() { return atmTransactionHistory; }
    void setLanguage();
    bool isAdmin(string cardNumberInput);
    void handleAdminSession();
    bool writeHistoryToFile(const string& historyContent) const;
    bool handleUserSession(string cardNumberInput);
    bool isSingle();
    bool isValid(string cardNumberInput);

    // 입출금
    void addCashToATM(const CashDenominations& deposit);
    bool dispenseCash(long amount);

    CashDenominations getCash() const { return availableCash; }
};

#endif
