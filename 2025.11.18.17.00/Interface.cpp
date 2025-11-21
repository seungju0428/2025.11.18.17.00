#include "Interface.h"
#include <string>
#include <iostream>
#include <vector>
#include "main.h"
#include "ATM.h"
using namespace std;

Interface::Interface() { addMessages(); } // 생성자



//===================================================================
// 메세지 맵에 문구 추가 (parameter 불필요)
//===================================================================
void Interface::addMessages() {
	// ATM의 언어가 정해지기 전
	msgMap["InitializationStart"]["Unselected"] =
		"======================================================================================================\n"
		"[ System Initialization | 시스템 초기화 ]\n"
		"------------------------------------------------------------------------------------------------------\n"
		"Enter the initial configuration file path. (초기 설정 파일 경로를 입력하세요.)\n"
		"> ";
	msgMap["FileOpenSuccess"]["Unselected"] = "\nFile opened successfully (파일 열기 성공)\n";
	msgMap["FileOpenFail"]["Unselected"] = "\nFailed to open file (파일 열기 실패)\n";
	msgMap["EnterATMSerialNumber"]["Unselected"] = 
		"Enter ATM's serial number. (ATM의 고유번호를 입력하세요.)\n"
		"> ";
	msgMap["ChooseLanguage"]["Unselected"] = 
		"Choose one language. [English/Korean] (언어를 선택하세요. [영어/한국어])\n"
		"> ";

	// ATM의 언어가 정해진 후
	msgMap["EnterCardNumber"]["English"] = 
		"\nInsert your card into the slot and enter the card number(Include '-'). (Enter 'Back' to quit.)\n"
		"> ";
	msgMap["EnterCardNumber"]["Korean"] = 
		"\n카드를 슬롯에 삽입하고 카드 번호('-' 포함)를 입력하세요. (나가려면 '이전'을 입력하세요.)\n"
		"> ";

	msgMap["CheckValidity"]["English"] = "Checking card validity... ";
	msgMap["CheckValidity"]["Korean"] = "카드 유효성 확인 중... ";

	msgMap["IsNotValid"]["English"] = "Card is not accepted.\n";
	msgMap["IsNotValid"]["Korean"] = "카드 사용 불가\n";

	msgMap["IsValid"]["English"] = "Card accepted\n";
	msgMap["IsValid"]["Korean"] = "카드 사용 가능\n";
	
	msgMap["SessionStart"]["English"] = "Session is started.\n";
	msgMap["SessionStart"]["Korean"] = "세션이 시작되었습니다.\n";

	msgMap["TransactionHistoryMenu"]["English"] =
		"======================================================================================================\n"
		"[ Transaction History Menu ]\n"
		"------------------------------------------------------------------------------------------------------\n"
		"1. Viewing and exporting this ATM's transaction history\n"
		"2. Quit\n"
		"> ";
	msgMap["TransactionHistoryMenu"]["Korean"] =
		"======================================================================================================\n"
		"[ 거래 내역 메뉴 ]\n"
		"------------------------------------------------------------------------------------------------------\n"
		"1. 이 ATM의 거래 내역 열람 및 추출\n"
		"2. 나가기\n"
		"> ";

	msgMap["WritingHistoryToFile"]["English"] = "Exporting transaction history to enternal file.\n";
	msgMap["WritingHistoryToFile"]["Korean"] = "거래 기록을 외부 파일로 내보내는 중입니다.\n";

	msgMap["FileWritingSuccess"]["English"] = "File exported successfully\n";
	msgMap["FileWritingSuccess"]["Korean"] = "파일을 성공적으로 내보냈습니다.\n";

	msgMap["FileWritingFailure"]["English"] = "Failed to export file\n";
	msgMap["FileWritingFailure"]["Korean"] = "파일 내보내기에 실패했습니다.\n";

	msgMap["EnterCardPW"]["English"] = 
		"\nEnter card password\n"
		"> ";
	msgMap["EnterCardPW"]["Korean"] = 
		"\n카드 비밀번호를 입력하세요.\n"
		"> ";

	msgMap["CorrectCardPW"]["English"] = "Correct password\n";
	msgMap["CorrectCardPW"]["Korean"] = "비밀번호 일치\n";

	msgMap["WrongCardPW"]["English"] = "Wrong password\n";
	msgMap["WrongCardPW"]["Korean"] = "잘못된 비밀번호\n";

	msgMap["PwIncorrect3Times"]["English"] = "Incorrect password entered three times in a row.\n";
	msgMap["PwIncorrect3Times"]["Korean"] = "비밀번호가 3번 연속으로 잘못 입력되었습니다.\n";

	msgMap["SessionMenu"]["English"] = 
		"======================================================================================================\n"
		"[ Session Menu ]\n"
		"------------------------------------------------------------------------------------------------------\n"
		"1. Deposit\n"
		"2. Withdrawal\n"
		"3. Transition\n"
		"Enter the transaction number.\n"
		"> ";
	msgMap["SessionMenu"]["Korean"] = 
		"======================================================================================================\n"
		"[ 세션 메뉴 ]\n"
		"------------------------------------------------------------------------------------------------------\n"
		"1. 입금\n"
		"2. 출금\n"
		"3. 이체\n"
		"거래 번호를 입력하세요.\n"
		"> ";

	msgMap["SessionEnd"]["English"] = "Session is ended.\n";
	msgMap["SessionEnd"]["Korean"] = "세션이 종료되었습니다.\n";

	msgMap["GoBackToEnteringCardNumber"]["English"] = "Returning to the card insertion and card number entry step.\n";
	msgMap["GoBackToEnteringCardNumber"]["Korean"] = "카드 삽입 및 카드 번호 입력 단계로 돌아갑니다.\n";
	
	msgMap["AskDepositType"]["English"] =
		"1. Cash Deposit\n"
		"2. Check Deposit\n"
		"Enter deposit type number.\n"
		"> ";
	msgMap["AskDepositType"]["Korean"] = 
		"1. 현금 입금\n"
		"2. 수표 입금\n"
		"입금 종류 번호를 입력하세요.\n"
		"> ";

	msgMap["Input50kCount"]["English"] =
		"Enter the number of 50000Won.\n"
		"> ";
	msgMap["Input50kCount"]["Korean"] =
		"50000원의 장수를 입력하세요.\n"
		"> ";
	
	msgMap["Input10kCount"]["English"] =
		"Enter the number of 10000Won.\n"
		"> ";
	msgMap["Input10kCount"]["Korean"] =
		"10000원의 장수를 입력하세요.\n"
		"> ";

	msgMap["Input5kCount"]["English"] =
		"Enter the number of 5000Won.\n"
		"> ";
	msgMap["Input5kCount"]["Korean"] =
		"5000원의 장수를 입력하세요.\n"
		"> ";

	msgMap["Input1kCount"]["English"] =
		"Enter the number of 1000Won.\n"
		"> ";
	msgMap["Input1kCount"]["Korean"] =
		"1000원의 장수를 입력하세요.\n"
		"> ";

	msgMap["InvalidInput_Number"]["English"] = "Please enter number.\n";
	msgMap["InvalidInput_Number"]["Korean"] = "숫자를 입력해 주십시오.\n";

	msgMap["InvalidInput_Negative"]["English"] = "Negative number can not be accepted.\n";
	msgMap["InvalidInput_Negative"]["Korean"] = "음수는 입력할 수 없습니다.\n";

	msgMap["ExceedCashLimit"]["English"] = "Cash insertion limit exceeded. You can insert up to 50 notes.\n";
	msgMap["ExceedCashLimit"]["Korean"] = "현금 삽입 제한을 초과했습니다. 현금은 최대 50장까지만 삽입할 수 있습니다.\n";

	msgMap["NoCashInserted"]["English"] = "Cash is not inserted.\n";
	msgMap["NoCashInserted"]["Korean"] = "현금이 삽입되지 않았습니다.\n";

	msgMap["CheckInsertionRule"]["English"] = "수표 입력 조건 ~~(Eng.ver)\n";
	msgMap["CheckInsertionRule"]["Korean"] = "수표 입력 조건 ~~\n";
	
	msgMap["EnterCheckAmount"]["English"] =
		"수표 금액 입력. 그만 입력하려면 0 입력.(Eng.ver)\n"
		"> ";
	msgMap["EnterCheckAmount"]["Korean"] = 
		"수표 금액 입력. 그만 입력하려면 0 입력\n"
		"> ";

	msgMap["InvalidCheckAmount"]["English"] = "수표 금액 이상함요;;(Eng.ver)\n";
	msgMap["InvalidCheckAmount"]["Korean"] = "수표 금액 이상함요;;\n";

	msgMap["EnterCheckAmount"]["English"] =
		"수표 장수 입력(Eng.ver)\n"
		"> ";
	msgMap["EnterCheckAmount"]["Korean"] =
		"수표 장수 입력\n"
		"> ";

	msgMap["NoCheckInputExit"]["English"] = "수표 입력 안 됨(Eng.ver)\n";
	msgMap["NoCheckInputExit"]["Korean"] = "수표 입력 안 됨\n";

	msgMap["ExceedCheckLimit"]["English"] = "수표 장수 너무 많이 입력됨(Eng.ver)\n";
	msgMap["ExceedCheckLimit"]["Korean"] = "수표 장수 너무 많이 입력됨\n";

	msgMap["CheckInsertionConfirm"]["English"] = "수표 입력 완료!(Eng.ver)\n";
	msgMap["CheckInsertionConfirm"]["Korean"] = "수표 입력 완료!\n";
	
}



//===================================================================
// 메세지 맵에 문구 추가 (parameter 필요)								<< 추가->출력보다는 인자로 무언가 받고 바로 출력하는 거로 고치기
//===================================================================
void Interface::addMainMenu(const vector<ATM*>& allATMs) { // Initializer의 run 함수에서 실행됨
	string message;
	message += "======================================================================================================\n";
	message += "[ Main Menu | 메인 메뉴 ]\n";
	message += "------------------------------------------------------------------------------------------------------\n";
	message += "- ATM List (ATM 목록) -\n";
	int index = 1;
	for (ATM* atm : allATMs) {
		message += "#" + to_string(index++) + "\n";
		message += "Primary Bank (주거래은행) : " + atm->getPrimaryBank() + "\n";
		message += "ATM Serial (ATM 고유번호) : " + atm->getSerialNumber() + "\n";
		message += "Type (유형)               : " + atm->getType() + "\n";
		message += "Language (언어)           : " + atm->getLanguageMode() + "\n\n";
	}
	msgMap["MainMenu"]["Unselected"] = message;
}
void Interface::addATMWelcome(const ATM* atm) { // ATM의 run 함수에서 실행됨
	string message;
	message += "======================================================================================================\n";
	message += "[ Welcome. ATM ";
	message += atm->getSerialNumber();
	message += " activated. | 환영합니다. ATM ";
	message += atm->getSerialNumber();
	message += "이 활성화되었습니다. ]\n";
	message += "------------------------------------------------------------------------------------------------------\n";
	msgMap["ATMWelcome"]["Unselected"] = message;
}
void Interface::addLanguageModeNotification(string languageMode) { // ATM의 run 함수에서 실행됨
	if (languageMode == "Bilingual") {
		msgMap["LanguageModeNotification"]["English"] = "Language is set to English.\n";
		msgMap["LanguageModeNotification"]["Korean"] = "언어가 한국어로 설정되었습니다.\n";
	}
	else if (languageMode == "Unilingual") {
		msgMap["LanguageModeNotification"]["English"] = "Since this is a unilingual ATM, language is set to English.\n";
	}
}



//===================================================================
// 메세지 맵 안의 메세지 출력
//===================================================================
void Interface::displayMessage(string msgKey) {
	cout << msgMap[msgKey][language];
}



//===================================================================
// 기타 함수 
//===================================================================
int Interface::inputInt(string msgKey) { // Cash Deposit, Check Deposit에서 사용
	int count;
	while (true) {
		cout << msgMap[msgKey][language];
		cin >> count;
		if (cin.fail()) {
			cin.clear(); // 에러 플래그 초기화--
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기
			cout << msgMap["InvalidInput_Number"][language] << endl; // "숫자만 입력해주세요."
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 뒤에 남은 엔터 제거
			if (count < 0) {
				cout << msgMap["InvalidInput_Negative"][language]; // "음수는 입력할 수 없습니다."
				continue;
			}
			return count;
		}
	}
}

long Interface::inputCheckAmount(string msgKey) { // Check Deposit에서 사용
	long amount;
	while (true) {
		cout << msgMap[msgKey][language];
		cin >> amount;
		if (cin.fail()) {
			cin.clear(); // 에러 플래그 초기화--
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기
			cout << msgMap["InvalidInput_Number"][language] << endl; // "숫자만 입력해주세요."
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 뒤에 남은 엔터 제거
			if (amount < 0) {
				cout << msgMap["InvalidInput_Negative"][language]; // "음수는 입력할 수 없습니다."
				continue;
			}
			return amount;
		}
	}
}

void Interface::totalCheckInfo(int amount, int count) {
	if (language == "English") {
		cout << "(Eng.ver)현재까지 입력된 수표의 총액:  " << amount << "원\n 현재까지 입력된 수표의 총 장수: " << count << "장\n";
	}
	else if (language == "Korean") {
		cout << "현재까지 입력된 수표의 총액:  " << amount << "원\n 현재까지 입력된 수표의 총 장수: " << count << "장\n";
	}
}