#include "DepositTransaction.h"
#include <iostream>
#include "Interface.h"

void DepositTransaction::run() {
	ui.displayMessage("AskDepositType");
	int choice;
	cin >> choice;
	switch (choice) { // 1. 현금 입금 vs 수표 입금
	case 1:
		handleCashDeposit();
	case 2:
		handleCheckDeposit();
	}
	// 2. 수수료 현금으로 받기
	// 3. ATM 보유 현금 업데이트
	// 4. 계좌 잔액 증가
	// 5. 결과 출력
	// 6. Account의 거래 내역 업뎃
ATM의 거래 내역 업뎃
}



//===================================================================
// run 외 함수들
//===================================================================
DepositTransaction::DepositTransaction(Interface& uiInput) : Transaction(uiInput) {}

void DepositTransaction::handleCashDeposit() {
	// 1. 권종별 매수 입력
	int cnt50k = ui.inputInt("Input50kCount");
	int cnt10k = ui.inputInt("Input10kCount");
	int cnt5k = ui.inputInt("Input5kCount");
	int cnt1k = ui.inputInt("Input1kCount");

	// 2. 현금 입력 조건 검증
	int totalBills = cnt50k + cnt10k + cnt5k + cnt1k;
	if (totalBills > 50) { ui.displayMessage("ExceedCashLimit"); return; } // 현금 삽입에서 오류 발생하면 현금 삽입하는 단계로 돌아가는 게 낫지 않나?
	if (totalBills == 0) { ui.displayMessage("NoCashInserted"); return; }
}

void DepositTransaction::handleCheckDeposit() {
    long totalCheckAmount = 0;
    int totalCheckCount = 0;
    ui.displayMessage("CheckInsertionRule");
    while (true) { // 1. 수표 입력 반복
        // 수표 금액 입력
        long amount = ui.inputCheckAmount("EnterCheckAmount");
        // 수표 유효성 검사
        if (amount == 0) break;
        if (amount < 100000) { ui.displayMessage("InvalidCheckAmount"); continue; }
        // 해당 수표의 장수 입력
        int count = ui.inputInt("EnterCheckCount");
        if (count <= 0) { ui.displayMessage("InvalidInput_Negative"); continue; }
        // 누적 수표 금액 및 장수 출력
        totalCheckAmount += (amount * count);
        totalCheckCount += count;
        ui.totalCheckInfo(totalCheckAmount, totalCheckCount);
    }
    // 2. 수표 입력 조건 검증
    if (totalCheckCount == 0) { ui.displayMessage("NoCheckInputExit"); return; }
    if (totalCheckCount > 30) { ui.displayMessage("ExceedCheckLimit"); return; }

    // 3. 입력 받은 수표 확인 메시지 출력
    cout << "---------------------------------" << endl;
    ui.totalCheckInfo(totalCheckAmount, totalCheckCount);
    ui.displayMessage("CheckInsertionConfirm");
    cout << "---------------------------------" << endl;
}
