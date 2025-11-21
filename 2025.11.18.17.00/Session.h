#ifndef SESSION_H
#define SESSION_H
#include "Interface.h"
#include "Bank.h"
#include "Account.h"
#include "DepositTransaction.h"
#include "WithdrawalTransaction.h"
#include "TransferTransaction.h"
#include <vector>
#include <map>

class ATM;
class Transaction;

class Session {
private:
	Bank* pBank;
	Account* pAccount;
	Interface& ui;
	ATM* pATM; 
    map<string, Bank*>& allBanks;
    int withdrawalCount;
    vector<string> historyLog;
	Transaction* deposit;
	Transaction* withdrawal;
	Transaction* transfer;


public:
	Session(Bank* pBank, Account* pAccount, Interface& ui, ATM* atm, map<string, Bank*>& banks);
	~Session()
	// 추가
	Interface& getUI() { return ui; }
	Bank* getBank() { return pBank; }
	Account* getAccount() { return pAccount; }
	ATM* getATM() {return pATM;}
	제공해주신 최신 Interface 코드와 Transaction 코드들을 분석한 결과, Transaction 로직이 정상적으로 돌아가기 위해 필요한 데이터 접근 함수(Getter)와 연결 고리들이 Account, Bank, Initializer, ATM, Session에 누락되어 있습니다.

또한, Interface::addMessages에 Transaction에서 사용하는 메세지 키(Key)들이 대거 빠져 있어 실행 시 오류가 발생할 수 있습니다.

이를 보완한 코드를 정리해 드립니다.

1. Interface.cpp (메세지 키 추가)
Transaction 클래스들에서 displayMessage("FeeNoticePart1") 등을 호출하고 있지만, 현재 addMessages()에는 해당 키가 없습니다. 아래 내용을 addMessages() 함수 끝부분에 추가해야 합니다.

C++

// Interface.cpp의 addMessages() 함수 내부에 추가

	// ... (기존 코드) ...

	// [추가] 공통 단위 및 라벨
	msgMap["WonUnit"]["English"] = " KRW";
	msgMap["WonUnit"]["Korean"] = "원";
	msgMap["SheetUnit"]["English"] = " sheets";
	msgMap["SheetUnit"]["Korean"] = "장";
	msgMap["FeeLabel"]["English"] = "Fee: ";
	msgMap["FeeLabel"]["Korean"] = "수수료: ";

	// [추가] 수수료 관련
	msgMap["FeeNoticePart1"]["English"] = "Transaction Fee: ";
	msgMap["FeeNoticePart1"]["Korean"] = "수수료 ";
	msgMap["FeeNoticePart2"]["English"] = " KRW is required.";
	msgMap["FeeNoticePart2"]["Korean"] = "원이 필요합니다.";
	msgMap["FeePromptPart1"]["English"] = "Please insert ";
	msgMap["FeePromptPart1"]["Korean"] = "1000원권 ";
	msgMap["FeePromptPart2"]["English"] = " bill(s) of 1000 KRW for fee.\n> ";
	msgMap["FeePromptPart2"]["Korean"] = "장을 넣어주세요.\n> ";
	msgMap["InsufficientFee"]["English"] = "Insufficient fee inserted.\n";
	msgMap["InsufficientFee"]["Korean"] = "수수료가 부족합니다.\n";

	// [추가] 입금 관련
	msgMap["DepositSuccess"]["English"] = "Deposit Successful!\n";
	msgMap["DepositSuccess"]["Korean"] = "입금 성공!\n";
	msgMap["DepositFailed"]["English"] = "Deposit Failed.\n";
	msgMap["DepositFailed"]["Korean"] = "입금 실패.\n";
	msgMap["DepositAmountLabel"]["English"] = "Deposited Amount: ";
	msgMap["DepositAmountLabel"]["Korean"] = "입금액: ";
	msgMap["TotalDepositAmountLabel"]["English"] = "Total Deposited: ";
	msgMap["TotalDepositAmountLabel"]["Korean"] = "총 입금액: ";

	// [추가] 수표 관련 (누락된 부분 보완)
	msgMap["StartCheckDepositInfo"]["English"] = "Start Check Deposit process.\n";
	msgMap["StartCheckDepositInfo"]["Korean"] = "수표 입금을 시작합니다.\n";
	msgMap["PromptCheckAmountLoop"]["English"] = "Enter check amount (0 to finish)\n> ";
	msgMap["PromptCheckAmountLoop"]["Korean"] = "수표 금액 입력 (종료하려면 0)\n> ";
	msgMap["PromptCheckCount"]["English"] = "Enter number of checks\n> ";
	msgMap["PromptCheckCount"]["Korean"] = "수표 장수 입력\n> ";
	msgMap["CheckTotalInfo"]["English"] = "Current Total: "; // totalCheckInfo 함수에서 사용
	msgMap["CheckTotalInfo"]["Korean"] = "현재 총액: ";
	msgMap["FinalCheckTotalAmount"]["English"] = "Final Check Amount: ";
	msgMap["FinalCheckTotalAmount"]["Korean"] = "최종 수표 총액: ";
	msgMap["FinalCheckTotalCount"]["English"] = "Final Check Count: ";
	msgMap["FinalCheckTotalCount"]["Korean"] = "최종 수표 장수: ";
	msgMap["FinalCheckDepositConfirm"]["English"] = "Confirming deposit...\n";
	msgMap["FinalCheckDepositConfirm"]["Korean"] = "입금을 확정합니다...\n";
	msgMap["CheckDepositSuccess"]["English"] = "Check Deposit Successful!\n";
	msgMap["CheckDepositSuccess"]["Korean"] = "수표 입금 성공!\n";

	// [추가] 출금 관련
	msgMap["CurrentBalance"]["English"] = "Current Balance: ";
	msgMap["CurrentBalance"]["Korean"] = "현재 잔액: ";
	msgMap["WithdrawalAmountPrompt"]["English"] = "Enter amount to withdraw\n> ";
	msgMap["WithdrawalAmountPrompt"]["Korean"] = "출금할 금액을 입력하세요\n> ";
	msgMap["ExceedWithdrawalLimit"]["English"] = "Exceeded max withdrawal limit (500,000 KRW).\n";
	msgMap["ExceedWithdrawalLimit"]["Korean"] = "1회 출금 한도(50만원)를 초과했습니다.\n";
	msgMap["InvalidAmountUnit"]["English"] = "Amount must be in 1,000 KRW units.\n";
	msgMap["InvalidAmountUnit"]["Korean"] = "1,000원 단위로 입력해주세요.\n";
	msgMap["InsufficientBalance"]["English"] = "Insufficient account balance.\n";
	msgMap["InsufficientBalance"]["Korean"] = "계좌 잔액이 부족합니다.\n";
	msgMap["InsufficientATMCash"]["English"] = "ATM has insufficient cash.\n";
	msgMap["InsufficientATMCash"]["Korean"] = "ATM 내 현금이 부족합니다.\n";
	msgMap["WithdrawalSuccess"]["English"] = "Withdrawal Successful!\n";
	msgMap["WithdrawalSuccess"]["Korean"] = "출금 성공!\n";
	msgMap["WithdrawalAmountLabel"]["English"] = "Withdrawn Amount: ";
	msgMap["WithdrawalAmountLabel"]["Korean"] = "출금액: ";
	msgMap["BalanceAfterTransaction"]["English"] = "Balance after transaction: ";
	msgMap["BalanceAfterTransaction"]["Korean"] = "거래 후 잔액: ";
	msgMap["MaxWithdrawalLimitReached"]["English"] = "Max withdrawal count (3 times) reached.\n";
	msgMap["MaxWithdrawalLimitReached"]["Korean"] = "세션 당 최대 출금 횟수(3회)에 도달했습니다.\n";
	msgMap["AskAdditionalWithdrawal"]["English"] = "1. Withdraw more\n2. Quit\n> ";
	msgMap["AskAdditionalWithdrawal"]["Korean"] = "1. 추가 출금\n2. 종료\n> ";
	msgMap["ReturningToMenu"]["English"] = "Returning to menu...\n";
	msgMap["ReturningToMenu"]["Korean"] = "메뉴로 돌아갑니다...\n";
	msgMap["TransactionCancelled"]["English"] = "Transaction Cancelled.\n";
	msgMap["TransactionCancelled"]["Korean"] = "거래가 취소되었습니다.\n";
	msgMap["TransactionFailed"]["English"] = "Transaction Failed.\n";
	msgMap["TransactionFailed"]["Korean"] = "거래 실패.\n";

	// [추가] 이체 관련
	msgMap["TransferOptionMenu"]["English"] = "1. Cash Transfer\n2. Account Transfer\n> ";
	msgMap["TransferOptionMenu"]["Korean"] = "1. 현금 송금\n2. 계좌 이체\n> ";
	msgMap["CashTransferInputGuide"]["English"] = "Please insert cash for transfer.\n";
	msgMap["CashTransferInputGuide"]["Korean"] = "송금할 현금을 투입해주세요.\n";
	msgMap["AccountNumPrompt"]["English"] = "Enter destination account number\n> ";
	msgMap["AccountNumPrompt"]["Korean"] = "받으실 분의 계좌번호를 입력하세요\n> ";
	msgMap["TransferToSelfError"]["English"] = "Cannot transfer to the same account.\n";
	msgMap["TransferToSelfError"]["Korean"] = "자신의 계좌로는 이체할 수 없습니다.\n";
	msgMap["InvalidAccount"]["English"] = "Invalid account number.\n";
	msgMap["InvalidAccount"]["Korean"] = "존재하지 않는 계좌입니다.\n";
	msgMap["TransferAmountPrompt"]["English"] = "Enter transfer amount\n> ";
	msgMap["TransferAmountPrompt"]["Korean"] = "이체할 금액을 입력하세요\n> ";
	msgMap["TransferSuccess"]["English"] = "Transfer Successful!\n";
	msgMap["TransferSuccess"]["Korean"] = "이체 성공!\n";
	msgMap["TransferAmountLabel"]["English"] = "Transferred Amount: ";
	msgMap["TransferAmountLabel"]["Korean"] = "이체 금액: ";
	msgMap["ReceiverLabel"]["English"] = "Receiver: ";
	msgMap["ReceiverLabel"]["Korean"] = "받는 분: ";
2. Account 수정
Transaction에서 getBalance(), getBankName(), getUserName()을 호출하므로 추가해야 합니다.

Account.h

C++

// public 부분에 추가
    string getBankName() const { return bankName; }
    string getUserName() const { return userName; }
    int getBalance() const { return balance; }
Account.cpp

C++

// 기존 addFunds, deductFunds 코드 유지
// 생성자에서 m_balance 가 아니라 balance로 초기화하는지 확인 (이미 수정된 것으로 보임)
3. Bank 수정
TransferTransaction에서 계좌번호로 계좌를 찾는 findAccount가 필요합니다.

Bank.h

C++

// public 부분에 추가
    Account* findAccount(string accountNumber);
Bank.cpp

C++

// 파일 하단에 구현
Account* Bank::findAccount(string accountNumber) {
    auto it = accounts.find(accountNumber);
    if (it != accounts.end()) {
        return it->second;
    }
    return nullptr;
}
4. Initializer 수정
ATM이 Session을 만들 때 모든 은행 정보(allBanks)를 넘겨주기 위해 Getter가 필요합니다.

Initializer.h

C++

// public 부분에 추가
    map<string, Bank*>& getAllBanks() { return allBanks; }
5. ATM 수정
Transaction에서 atm->getPrimaryBankName()을 호출하므로, 기존 getPrimaryBank()를 래핑하거나 이름을 맞춰줘야 합니다. 또한 run()에서 Session을 생성할 때 필요한 인자가 늘어났습니다.

ATM.h

C++

// public 부분에 추가
    // Transaction에서 호출하는 이름과 매칭
    string getPrimaryBankName() const { return getPrimaryBank(); }
ATM.cpp (run 함수 수정)

C++

void ATM::run() {
    // ... (기존 코드) ...

    while (true) {
        // ... (카드번호 입력) ...
        
        // [수정] Session 생성자에 ATM 포인터와 전체 은행 리스트 전달
        Session* session = new Session(
            pInit->findBankByCardNumber(cardNumberInput), 
            pInit->findAccountPtrByCardNumber(cardNumberInput), 
            ui,
            this,                 // ATM 포인터 추가
            pInit->getAllBanks()  // 전체 은행 리스트 추가
        );

        // ... (기존 코드) ...
    }
}
6. Session 수정 (핵심)
Transaction들이 Session을 통해 ATM, Bank 리스트, withdrawalCount 등에 접근할 수 있도록 멤버 변수와 Getter를 추가하고 생성자를 수정해야 합니다.

Session.h

C++

#ifndef SESSION_H
#define SESSION_H
#include "Interface.h"
#include "Bank.h"
#include "Account.h"
#include <vector>
#include <map>

// 전방 선언
class ATM;
class Transaction;

class Session {
private:
    Bank* pBank;
    Account* pAccount;
    Interface& ui;
    
    // [추가] Transaction에 필요한 정보들
    ATM* pATM; 
    map<string, Bank*>& allBanks;
    int withdrawalCount;
    vector<string> historyLog;

    Transaction* deposit;
    Transaction* withdrawal;
    Transaction* transfer;

public:
    // [수정] 생성자: ATM*와 은행 리스트 추가
    Session(Bank* pBank, Account* pAccount, Interface& ui, ATM* atm, map<string, Bank*>& banks);
    ~Session(); // 소멸자 (Transaction 해제용)

    void run();

    // [추가] Transaction에서 사용하는 Getter들
    Interface& getUI() { return ui; }
    Bank* getBank() { return pBank; }
    Account* getAccount() { return pAccount; }
    ATM* getATM() { return pATM; }
    map<string, Bank*>& getAllBanks() { return allBanks; }
	int getWithdrawalCount() const { return withdrawalCount; }
    void increaseWithdrawalCount() { withdrawalCount++; }

    // [추가] 거래 내역 기록 함수
    void recordTransaction(string log);
};

#endif
