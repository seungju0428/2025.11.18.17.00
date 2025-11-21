#ifndef ATM_H
#define ATM_H
#include <string>
class Initializer; // inlcude 문제로 전방 선언
#include "Bank.h"
#include "Interface.h"
using namespace std;

class ATM {
private:    
    Bank* pPrimaryBank;
    string serialNumber;
    string type;
    string languageMode;
    int c50k; // 돈 관련된 거 거래 파트 만질 때 수정해야 함
    int c10k;
    int c5k;
    int c1k;
    string adminCardNumber; // 0000-0000-0000 (고객의 카드 번호랑 아예 다른 구조로 만드는 게 안전하려나? ex. 00-00-00)
    string atmTransactionHistory;
    int index; // 세션 기록 관련된 부분에서 쓰려나?
    Initializer* pInit;
    Interface& ui;
public:
    void run();

    ATM(Bank* primaryBank, const string& serial, const string& t, const string& lang, int cash50k, int cash10k, int cash5k, int cash1k, Initializer* initializer, Interface& uiInput);
    string getPrimaryBank() const { return pPrimaryBank->getPrimaryBank(); }
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
};

#endif