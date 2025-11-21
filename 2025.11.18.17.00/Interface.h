#ifndef INTERFACE_H
#define INTERFACE_H

#include <map>
#include <string>
#include <vector>
class ATM;   // include 순서 문제로 인해 전방 선언(Forward Declaration)
using namespace std;

class Interface {
private:
	map<string, map<string, string>> msgMap; // ATM의 언어가 정해진 후에 사용할 메세지 맵

public:
	Interface(); // 생성자

	// 메세지 맵에 메세지 추가
	void addMessages();
	void addMainMenu(const vector<ATM*>& allATMs);
	void addATMWelcome(const ATM* atm);
	void addLanguageModeNotification(string languageMode);

	// 메세지 맵 안의 메세지 출력
	void displayMessage(string msgKey);
	void displayErrorMessage(string msgKey);

	// 기타 함수
	int inputInt(string msgKey);
	long inputCheckAmount(string msgKey);
	void totalCheckInfo(int amount, int count);

	// 화면 일시 정지. 계속하려면 엔터 누르세요 와 동일함
	void wait();
};

#endif
