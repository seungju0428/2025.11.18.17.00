#include "ATM.h"
#include <iostream>
#include "Interface.h"
#include "main.h"
#include "Initializer.h"
#include "Session.h"
using namespace std;

void ATM::run() {
	// 1. 환영 메세지
	ui.addATMWelcome(this);
	ui.displayMessage("ATMWelcome");

	// 2. 언어 결정
	setLanguage();

	while (true) {
		// 3. 카드번호 입력 받기
		ui.displayMessage("EnterCardNumber");
		string cardNumberInput;
		cin >> cardNumberInput;
		
		// 4. 세션 시작
		ui.displayMessage("SessionStart");
		Session* session = new Session(pInit->findBankByCardNumber(cardNumberInput), pInit->findAccountPtrByCardNumber(cardNumberInput), ui);

		// 5. 관리자 카드 vs 고객 카드
		if (isAdmin(cardNumberInput)) { // 관리자 카드
			handleAdminSession();
			continue;
		}
		else if (handleUserSession(cardNumberInput) == false) continue; // 고객 카드 무효 -> 3번으로 돌아가기

		// 6. Session의 run 함수 실행
		session->run();

		delete session;
		ui.displayMessage("GoBackToEnteringCardNumber");
	}
}



//===================================================================
// run 외 함수들
//===================================================================
ATM::ATM(Bank* primaryBank, const string& serial, const string& t, const string& lang, int cash50k, int cash10k, int cash5k, int cash1k, Initializer* initializer, Interface& uiInput)
	: pPrimaryBank(primaryBank), serialNumber(serial), type(t), languageMode(lang), c50k(cash50k), c10k(cash10k), c5k(cash5k), c1k(cash1k), adminCardNumber("0000-0000-0000"), atmTransactionHistory(""), pInit(initializer), ui(uiInput), index(1) {} // 생성자

void ATM::setLanguage() {
	if (this->getLanguageMode() == "Bilingual") { // Bilingual
		ui.displayMessage("ChooseLanguage");
		cin >> language;
	}
	else { // Unilingual
		language = "English";
	}
	if (language == "영어") language = "English";
	else if (language == "한국어") language = "Korean";
	ui.addLanguageModeNotification(this->getLanguageMode());
	ui.displayMessage("LanguageModeNotification");
}

bool ATM::isAdmin(string cardNumberInput) {
	if (cardNumberInput == adminCardNumber) return true;
	else return false;
}

void ATM::handleAdminSession() { // 관리자 세션
	// 1. 거래 내역 메뉴 띄우기
	ui.displayMessage("TransactionHistoryMenu");

	// 2. 선택 입력 받기
	int choice;
	cin >> choice;

	switch (choice) {
	case 1: // 1 입력되면 거래 기록 열람 및 파일 제작
		cout << atmTransactionHistory << endl;
		ui.displayMessage("writingHistoryToFile");
		if (writeHistoryToFile(atmTransactionHistory)) { // 파일 내보내기 성공
			ui.displayMessage("fileWritingSuccess");
		}
		else { // 파일 내보내기 실패
			ui.displayMessage("fileWritingFailure");
		}
		ui.displayMessage("sessionEnd");
		break;
	case 2: // 2 입력되면 카드 번호 입력으로 돌아가기
		ui.displayMessage("GoBackToEnteringCardNumber");
		break;
	default:
		cout << "Invalid selection.\n";
		break;
	}
}

bool ATM::writeHistoryToFile(const string& historyContent) const { // 파일 내보내기
	string filename = "ATM_" + serialNumber + "_History_" + language + ".txt";
	ofstream outFile(filename);
	if (outFile.is_open()) {
		// 1. 파일 상단 내용 추가
		outFile << "[ ATM Information (ATM 정보) ]" << endl;
		outFile << "Primary Bank (주거래은행): " << pPrimaryBank->getPrimaryBank() << endl;
		outFile << "ATM Serial (ATM 고유번호): " << serialNumber << endl;
		outFile << "Type (유형): " << type << endl;
		outFile << "Language (언어): " << languageMode << endl;
		outFile << "========================================" << endl;
		outFile << "[ Transaction History (거래 내역) ]" << endl;
		// 2. 파일 본문 내용 추가
		outFile << historyContent;
		outFile.close();
		return true;
	}
	else {
		// 파일 열기 실패
		return false;
	}
}

bool ATM::handleUserSession(string cardNumberInput) { // 고객 세션
	ui.displayMessage("CheckValidity");
	if (isSingle()) { // Single ATM일 경우
		if (isValid(cardNumberInput) == false) { // 주거래은행의 카드인지 판단
			ui.displayMessage("IsNotValid");
			ui.displayMessage("SessionEnd");
			ui.displayMessage("GoBackToEnteringCardNumber");
			return false;
		}
	}
	ui.displayMessage("IsValid");
	return true;
}

bool ATM::isSingle() {
	if (this->getType() == "Single") return true;
	else return false;
}

bool ATM::isValid(string cardNumberInput) {
	if (pInit->findBankByCardNumber(cardNumberInput) == pPrimaryBank) return true;
	else return false;
}

