#ifndef	DEPOSITTRANSACTION_H
#define DEPOSITTRANSACTION_H

#include "Transaction.h"
#include "Interface.h"

class DepositTransaction : public Transaction {
private:
public:
	void run() override;

	DepositTransaction(Interface& uiInput);
	void handleCashDeposit();
	void handleCheckDeposit();
};

#endif