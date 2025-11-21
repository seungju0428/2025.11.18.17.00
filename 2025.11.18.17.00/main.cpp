#include "main.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include "Initializer.h"
using namespace std;

string language = "Unselected";

int main() { // 언제든지 입력으로 '/' 입력되면 ATM, Account 정보 출력 (REQ10.1)
	// 1. Interface 형식의 객체 ui 생성
	Interface ui;

	// 2. 파일 열기
	string filePath;
	ui.displayMessage("InitializationStart");
	getline(cin, filePath);

	// 3. fin에 파일 저장
	ifstream fin(filePath);
	if (!fin.is_open()) { // 파일 열기 실패
		ui.displayMessage("FileOpenFail");
		return 1;}
	ui.displayMessage("FileOpenSuccess"); // 파일 열기 성공

	// 4. Initializer class pointer 객체 생성
	Initializer* init = new Initializer(fin, ui); // 여기서 시스템 초기화

	// 5. Initializer의 run 함수 실행
	init->run();

	delete init;
	return 0;
}