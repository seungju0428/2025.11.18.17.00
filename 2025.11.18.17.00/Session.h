#ifndef SESSION_H
#define SESSION_H
#include "Interface.h"
#include "Bank.h"
#include "Account.h"
#include "DepositTransaction.h"
#include "WithdrawalTransaction.h"
#include "TransferTransaction.h"
#include <vector>
#include <map>

class ATM;
class Transaction;

class Session {
private:
	Bank* pBank;
	Account* pAccount;
	Interface& ui;
	ATM* pATM; 
    map<string, Bank*>& allBanks;
    int withdrawalCount;
    vector<string> historyLog;
	Transaction* deposit;
	Transaction* withdrawal;
	Transaction* transfer;


public:
	Session(Bank* pBank, Account* pAccount, Interface& ui, ATM* atm, map<string, Bank*>& banks);
	~Session()
	// 추가
	Interface& getUI() { return ui; }
	Bank* getBank() { return pBank; }
	Account* getAccount() { return pAccount; }
	ATM* getATM() {return pATM;}
	int getWirhdrawalCount() const {return withdrawalCount;}
	void increaseWithdrawalCount() { withdrawalCount ++ ;}

	// 거래 내역
	void recordTransaction()
