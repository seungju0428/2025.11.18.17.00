#ifndef SESSION_H
#define SESSION_H
#include "Interface.h"
#include "Bank.h"
#include "Account.h"
#include "DepositTransaction.h"
#include "WithdrawalTransaction.h"
#include "TransferTransaction.h"

class Session {
private:
	Bank* pBank;
	Account* pAccount;
	Interface& ui;
	Transaction* deposit;
	Transaction* withdrawal;
	Transaction* transfer;


public:
	Session(Bank* pBank, Account* pAccount, Interface& ui);
	// 추가
	Interface& getUI() { return ui; }
	Bank* getBank() { return pBank; }
	Account* getAccount() { return pAccount; }
	// --
	void run();
};

#endif
