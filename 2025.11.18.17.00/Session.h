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
	DepositTransaction* deposit;
	WithdrawalTransaction* withdrawal;
	TransferTransaction* transfer;


public:
	Session(Bank* pBank, Account* pAccount, Interface& ui);
	void run();
};

#endif