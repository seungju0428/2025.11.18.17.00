#include "Account.h"
#include <string>
using namespace std;

Account::Account(const string& bank, const string& user, const string& accNum, int bal, const string& cardNum, const string& cardPw, const string& transactionHistory)
	: bankName(bank), userName(user), accountNumber(accNum), balance(bal), cardNumber(cardNum), cardPassword(cardPw), transactionHistories(transactionHistory) {} // »ý¼ºÀÚ

