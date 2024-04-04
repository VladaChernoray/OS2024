#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

int queue = 1;
bool flags[2] = {false, false};

bool paymentRequested = false;
vector<pair<int, int>> bills = {{100, 2}, {50, 2}, {20, 3}, {10, 10}, {5, 2}, {2, 5}, {1, 7}};

struct Bill {
    int nominal;
    int count;
};

bool check_bank_account(int customer_account, int amount) {
    return (amount <= customer_account);
}

pair<bool, vector<Bill>> possibility_of_payment(int amount, vector<pair<int, int>>& bills) {
    sort(bills.rbegin(), bills.rend());
    vector<Bill> usedBills;

    for (int i = 0; i < bills.size(); ++i) {
        int billNominal = bills[i].first;
        int billCount = min(amount / billNominal, bills[i].second);
        amount -= billCount * billNominal;

        if (billCount > 0) {
            usedBills.push_back({billNominal, billCount});
        }

        if (amount == 0)
            return {true, usedBills};
    }
    return {false, usedBills};
}

void make_payment(int& customer_account, vector<pair<int, int>>& bills, const vector<Bill>& usedBills) {
    int totalAmount = 0;
    for (const auto& usedBill : usedBills) {
        totalAmount += usedBill.nominal * usedBill.count;
    }
    customer_account -= totalAmount;

    for (const auto& usedBill : usedBills) {
        for (auto& bill : bills) {
            if (bill.first == usedBill.nominal) {
                bill.second -= usedBill.count;
                break;
            }
        }
    }

    cout << "Payment successful. Client's account balance: " << customer_account << " grn" << endl;
}

void process_A(int& amount, int& customer_account) {
    while (true) {
        flags[0] = true;
        while (flags[1]) {
            if (queue == 2) {
                flags[0] = false;
                while (queue == 2)
                    ;
                flags[0] = true;
            }
        }

        amount = rand() % 100 + 1;
        cout << endl << "Withdrawal request received: " << amount << " grn" << endl; 
        paymentRequested = true; 

        flags[0] = false;
        queue = 2;

        this_thread::sleep_for(chrono::milliseconds(1500));
    }
}

void process_B(int& amount, int& customer_account) {
    while (true) {
        flags[1] = true;
        while (flags[0]) {
            if (queue == 1) {
                flags[1] = false;
                while (queue == 1)
                    ;
                flags[1] = true;
            }
        }
        // Critical Section
        if (paymentRequested) {
            if (check_bank_account(customer_account, amount)) {
                auto result = possibility_of_payment(amount, bills);
                if (result.first) {
                    cout << "Payment is possible. Used bills:" << endl; 
                    for (const auto& bill : result.second) {
                        cout << "Nominal: " << bill.nominal << ", Count: " << bill.count << endl; 
                    }
                    make_payment(customer_account, bills, result.second);
                } 
                else {
					cout << "Payment is not possible. Not enough banknotes at ATM. ATM balance: " << endl;
					for (const auto& bill : bills) {
						cout << "Nominal: " << bill.first << ", Count: " << bill.second << endl;
					}
				}
            }
            else cout << "Payment is not possible. Not enough funds in the bank account. Client's account balance: " << customer_account << " grn" << endl;
        }

        paymentRequested = false;
        flags[1] = false;
        queue = 1;

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {
    srand(time(nullptr)); 
    int amount = 0; 
    int customer_account = 1000; 

    thread t1(process_A, std::ref(amount), std::ref(customer_account));
    thread t2(process_B, std::ref(amount), std::ref(customer_account));

    t1.join();
    t2.join();

    return 0;
}
