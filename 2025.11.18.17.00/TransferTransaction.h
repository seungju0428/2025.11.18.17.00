#ifndef TRANSFER_TRANSACTION_H
#define TRANSFER_TRANSACTION_H

#include "Transaction.h"

class Account;

class TransferTransaction : public Transaction {
private:
    Account* findDestinationAccount(const string& destAccNum);
    void processCashTransfer(long fee, Account* destAccount);
    void processAccountTransfer(long fee, Account* destAccount);

public:
    TransferTransaction(Session* session);
    void run() override;
};    

#endif
