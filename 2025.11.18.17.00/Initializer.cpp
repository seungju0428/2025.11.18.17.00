#include "Initializer.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "main.h"
#include "Interface.h"
#include "ATM.h"
#include "Account.h"

void Initializer::run() {
    ui.addMainMenu(allATMs);
    while (true) {
        // 1. 메인메뉴 띄우기
        ui.displayMessage("MainMenu");

        // 2. ATM serial number 입력 받기
        ui.displayMessage("EnterATMSerialNumber");
        string serialNumberInput;
        cin >> serialNumberInput;

        // 3. ATM serial로 ATM 주소 찾기 // 4. ATM의 run 함수 실행
        findATMBySerialNumber(serialNumberInput)->run();
    }
}



//===================================================================
// run 외 함수들
//===================================================================
Initializer::Initializer(ifstream& fin, Interface& uiInput) : ui(uiInput) { // 생성자
    // 줄1: 은행 수 B, 계좌 수 A, ATM 수 N
    int B, A, N;
    fin >> B >> A >> N;
    fin.ignore();

    // 줄2~(B+1): Bank 이름
    for (int i = 0; i < B; i++) {
        string bankName;
        getline(fin, bankName);
        // Bank 객체 생성
        Bank* pBank = new Bank(bankName);
        // Bank 맵에 추가
        allBanks[bankName] = pBank; // key: 은행 이름
    }

    // 줄(B+2)~(B+1+6A): Account 정보 (Account 당 정보 6개 보유)
    for (int i = 0; i < A; i++) {
        string bankName;
        string userName;
        string accountNumber;
        string availableFundsStr;
        string cardNumber;
        string cardPassword;
        string transactionHistories;
        getline(fin, bankName);
        getline(fin, userName);
        getline(fin, accountNumber);
        getline(fin, availableFundsStr);
        getline(fin, cardNumber);
        getline(fin, cardPassword);
        transactionHistories = "";
        int availableFunds = stoi(availableFundsStr);
        // Account 객체 생성
        Account* pAccount = new Account(
            bankName,
            userName,
            accountNumber,
            availableFunds,
            cardNumber,
            cardPassword,
            transactionHistories
        );
        // Bank의 accounts 맵에 추가
        allBanks[bankName]->addAccount(pAccount);
    }

    // 줄(B+2+6A)~: ATM 정보 (ATM 당 정보 5개 보유)
    for (int i = 0; i < N; i++) {
        string primaryBank;
        string serial;
        string type;
        string languageMode;
        string initialFund;
        getline(fin, primaryBank);
        getline(fin, serial);
        getline(fin, type);
        getline(fin, languageMode);
        getline(fin, initialFund);
        // initialFund를 현금 단위별 장수로 분리
        int c50k, c10k, c5k, c1k;
        {
            stringstream ss(initialFund);
            ss >> c50k >> c10k >> c5k >> c1k;
        }
        // ATM 객체 생성
        ATM* pATM = new ATM(
            allBanks[primaryBank],
            serial,
            type,
            languageMode,
            c50k,
            c10k,
            c5k,
            c1k,
            this,
            ui
        );
        // ATM 벡터에 추가
        allATMs.push_back(pATM);
    }

    cout << "Initialization Completed (초기화 완료) " << endl;
}

ATM* Initializer::findATMBySerialNumber(string serialNumberInput) {
    for (ATM* atm : allATMs) {
        if (atm->getSerialNumber() == serialNumberInput) return atm;
    }
}

Bank* Initializer::findBankByCardNumber(string cardNumberInput) { // ATM의 run 함수에서 사용
    for (auto const& pair : allBanks) {
        Bank* pBank = pair.second;
        Bank* result = pBank->getBankByCardNumber(cardNumberInput);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}

Account* Initializer::findAccountPtrByCardNumber(string cardNumberInput) { // Session에서 사용
    for (auto const& pair : allBanks) {
        Bank* pBank = pair.second;
        Account* result = pBank->getAccountPtrByCardNumber(cardNumberInput);
        if (result != nullptr) {
            return result;
        }
    }
    return nullptr;
}