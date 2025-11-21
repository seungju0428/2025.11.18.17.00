#ifndef	TRANSFERTRANSACTION_H
#define TRANSFERTRANSACTION_H

#include "Transaction.h"

class TransferTransaction : public Transaction {
public:
	void run() override;
	
	TransferTransaction(Interface& uiInput);
};

#endif