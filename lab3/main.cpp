#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

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

bool check_payment_possibility(int amount, const vector<pair<int, int>>& bills) {
    int remainingAmount = amount;
    for (const auto& bill : bills) {
        int billNominal = bill.first;
        int billCount = min(remainingAmount / billNominal, bill.second);
        remainingAmount -= billCount * billNominal;
        if (remainingAmount == 0)
            return true;
    }
    return false;
}

vector<Bill> calculate_used_bills(int amount, vector<pair<int, int>>& bills) {
    vector<Bill> usedBills;
    for (const auto& bill : bills) {
        int billNominal = bill.first;
        int billCount = min(amount / billNominal, bill.second);
        amount -= billCount * billNominal;
        if (billCount > 0) {
            usedBills.push_back({billNominal, billCount});
        }
        if (amount == 0) break;
    }
    return usedBills;
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

        if (check_bank_account(customer_account, amount)) {
            if (check_payment_possibility(amount, bills)) {
                paymentRequested = true;
            } else {
                cout << "Payment is not possible. Not enough banknotes at ATM. ATM balance: " << endl;
                for (const auto& bill : bills) {
                    cout << "Nominal: " << bill.first << ", Count: " << bill.second << endl;
                }
            }
        } else
            cout << "Payment is not possible. Not enough funds in the bank account. Client's account balance: " 
            << customer_account << " grn" << endl;

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
        if (paymentRequested) {
            auto usedBills = calculate_used_bills(amount, bills);
            cout << "Payment is possible. Used bills:" << endl;
            for (const auto& bill : usedBills) {
                cout << "Nominal: " << bill.nominal << ", Count: " << bill.count << endl;
            }
            make_payment(customer_account, bills, usedBills);
        }

        paymentRequested = false;
        flags[1] = false;
        queue = 1;

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main() {
    srand(time_t(nullptr));
    int amount = 0;
    int customer_account = 1000;

    thread t1(process_A, std::ref(amount), std::ref(customer_account));
    thread t2(process_B, std::ref(amount), std::ref(customer_account));

    t1.join();
    t2.join();

    return 0;
}
