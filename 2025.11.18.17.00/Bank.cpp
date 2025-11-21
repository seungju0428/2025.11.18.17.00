#include "Bank.h"
#include <string>
#include <map>
using namespace std;

Bank::Bank(const string& name)
    : bankName(name) {
}

void Bank::addAccount(Account* pAccount) {
    accounts[pAccount->getAccountNumber()] = pAccount; // key: 계좌번호
}

Bank* Bank::getBankByCardNumber(string cardNumberInput) { // Initializer의 findBankByCardNumber 함수에서 사용
	for (auto const& pair : accounts) {
		Account* pAccount = pair.second;
		if (cardNumberInput == pAccount->getCardNumber()) {
			return this;
		}
	}
	return nullptr;
}

Account* Bank::getAccountPtrByCardNumber(string cardNumberInput) {
	for (auto const& pair : accounts) {
		Account* pAccount = pair.second;
		if (cardNumberInput == pAccount->getCardNumber()) {
			return pAccount;
		}
	}
	return nullptr;
}

bool Bank::isCorrectCardPW(Account* pAccount, string cardPWInput) { // Session의 run 함수에서 사용
	if (pAccount->getCardPassword() == cardPWInput) return true;
	else return false;
}

Account* Bank::findAccount(string accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        return it->second;
    }
    return nullptr;
}
