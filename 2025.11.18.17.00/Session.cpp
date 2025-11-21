#include "Session.h"
#include <iostream>
#include <string>
#include "DepositTransaction.h"
#include "WithdrawalTransaction.h"
#include "TransferTransaction.h"
using namespace std;

void Session::run() {
	// 1. 카드 비번 입력 받기
	ui.displayMessage("EnterCardPW");
	string cardPWInput;
	for (int i = 0; i < 3; i++) { // 비번 입력 3번 제한
		cin >> cardPWInput;
		// 2. Bank에서 카드 비번 검증
		if (pBank->isCorrectCardPW(pAccount, cardPWInput)) { // 비번 일치
			ui.displayMessage("CorrectCardPW");
			break;
		}
		else ui.displayMessage("WrongCardPW"); // 잘못된 비번
		if (i == 2) {
			ui.displayMessage("PwIncorrect3Times");
			ui.displayMessage("SessionEnd");
			return;
		}
	}
	// 3. 세션 종료 조건 만족할 때까지 거래 반복
	while (true) {
		// 거래 메뉴 띄우기
		ui.displayMessage("SessionMenu");
		// 진행할 거래 유형 입력 받기
		int transactionNumberInput;
		cin >> transactionNumberInput;
		// 입력 받은 유형의 거래 클래스의 run 함수 실행
		switch (transactionNumberInput) {
		case 1:
			deposit->run();
			break;
		case 2:
			withdrawal->run();
			break;
		case 3:
			transfer->run();
			break;
		}
	}
}



//===================================================================
// run 외 함수들
//===================================================================
Session::Session(Bank* pBank, Account* pAccount, Interface& ui) : pBank(pBank), pAccount(pAccount), ui(ui) {
	deposit = new DepositTransaction(ui);
	withdrawal = new WithdrawalTransaction(ui);
	transfer = new TransferTransaction(ui);
}