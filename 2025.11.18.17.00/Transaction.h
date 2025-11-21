#ifndef	TRANSACTION_H
#define TRANSACTION_H
#include "Interface.h"

class Transaction {
private:
protected:
	Interface& ui;
public:
	Transaction(Interface& uiInput);
	virtual void run() = 0;
};

#endif