#ifndef	WITHDRAWALTRANSACTION_H
#define WITHDRAWALTRANSACTION_H

#include "Transaction.h"

class WithdrawalTransaction : public Transaction {
public:
	void run() override;

	WithdrawalTransaction(Interface& uiInput);
};

#endif