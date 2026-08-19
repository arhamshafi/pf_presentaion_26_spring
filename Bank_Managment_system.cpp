#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Maximum number of accounts supported by the project
const int MAX_ACCOUNTS = 100;

// Structure for storing bank account information
struct Account {
  int accountNumber;
  string name;
  string cnic;
  string phone;
  double balance;
};

// Function prototypes
int loadAccounts(Account accounts[]);
void saveAccounts(Account accounts[], int count);
void createAccount(Account accounts[], int &count);
void displayAccount(Account accounts[], int count);
void depositMoney(Account accounts[], int count);
void withdrawMoney(Account accounts[], int count);
void searchAccount(Account accounts[], int count);
void updateAccount(Account accounts[], int count);
void deleteAccount(Account accounts[], int &count);
void displayAllAccounts(Account accounts[], int count);
int findAccount(Account accounts[], int count, int number);
void showAccount(Account acc);
int getAccountNumber();
void clearInput();
void pauseScreen();

// Load accounts from the text file
int loadAccounts(Account accounts[]) {
  ifstream file("accounts.txt");
  int count = 0;

  if (!file) {
    return 0;
  }

  while (count < MAX_ACCOUNTS) {
    string balanceText;

    if (!(file >> accounts[count].accountNumber)) {
      break;
    }

    file.ignore(1000, '\n');

    getline(file, accounts[count].name, '|');
    getline(file, accounts[count].cnic, '|');
    getline(file, accounts[count].phone, '|');
    getline(file, balanceText);

    if (balanceText.empty()) {
      break;
    }

    // atof works with older Dev-C++ compilers
    accounts[count].balance = atof(balanceText.c_str());
    count++;
  }

  file.close();
  return count;
}

// Save all accounts to a text file
void saveAccounts(Account accounts[], int count) {
  ofstream file("accounts.txt");

  if (!file) {
    cout << "\nUnable to save account data.\n";
    return;
  }

  for (int i = 0; i < count; i++) {
    file << accounts[i].accountNumber << endl;
    file << accounts[i].name << "|";
    file << accounts[i].cnic << "|";
    file << accounts[i].phone << "|";
    file << fixed << setprecision(2) << accounts[i].balance << endl;
  }

  file.close();
}

// Create a new bank account
void createAccount(Account accounts[], int &count) {
  if (count >= MAX_ACCOUNTS) {
    cout << "\nBank storage is full.\n";
    return;
  }

  Account acc;

  cout << "\n========== CREATE ACCOUNT ==========\n";
  cout << "Enter account number: ";
  cin >> acc.accountNumber;

  if (findAccount(accounts, count, acc.accountNumber) != -1) {
    cout << "This account number already exists.\n";
    return;
  }

  clearInput();

  cout << "Enter customer name: ";
  getline(cin, acc.name);

  cout << "Enter CNIC/ID: ";
  getline(cin, acc.cnic);

  cout << "Enter phone number: ";
  getline(cin, acc.phone);

  cout << "Enter initial balance: ";
  cin >> acc.balance;

  if (cin.fail()) {
    cin.clear();
    clearInput();
    cout << "Invalid balance entered.\n";
    return;
  }

  if (acc.balance < 0) {
    cout << "Initial balance cannot be negative.\n";
    return;
  }

  accounts[count] = acc;
  count++;

  saveAccounts(accounts, count);

  cout << "\nAccount created successfully!\n";
}

// Display one account
void displayAccount(Account accounts[], int count) {
  int number = getAccountNumber();
  int index = findAccount(accounts, count, number);

  if (index == -1) {
    cout << "\nAccount not found.\n";
    return;
  }

  cout << "\n========== ACCOUNT DETAILS ==========\n";
  showAccount(accounts[index]);
}

// Deposit money
void depositMoney(Account accounts[], int count) {
  int number = getAccountNumber();
  int index = findAccount(accounts, count, number);

  if (index == -1) {
    cout << "\nAccount not found.\n";
    return;
  }

  double amount;

  cout << "Enter amount to deposit: ";
  cin >> amount;

  if (cin.fail()) {
    cin.clear();
    clearInput();
    cout << "Invalid amount entered.\n";
    return;
  }

  if (amount <= 0) {
    cout << "Amount must be greater than zero.\n";
    return;
  }

  accounts[index].balance += amount;
  saveAccounts(accounts, count);

  cout << "\nAmount deposited successfully.\n";
  cout << "New balance: " << fixed << setprecision(2) << accounts[index].balance
       << endl;
}

// Withdraw money
void withdrawMoney(Account accounts[], int count) {
  int number = getAccountNumber();
  int index = findAccount(accounts, count, number);

  if (index == -1) {
    cout << "\nAccount not found.\n";
    return;
  }

  double amount;

  cout << "Enter amount to withdraw: ";
  cin >> amount;

  if (cin.fail()) {
    cin.clear();
    clearInput();
    cout << "Invalid amount entered.\n";
    return;
  }

  if (amount <= 0) {
    cout << "Amount must be greater than zero.\n";
    return;
  }

  if (amount > accounts[index].balance) {
    cout << "Insufficient balance.\n";
    return;
  }

  accounts[index].balance -= amount;
  saveAccounts(accounts, count);

  cout << "\nAmount withdrawn successfully.\n";
  cout << "Remaining balance: " << fixed << setprecision(2)
       << accounts[index].balance << endl;
}

// Search an account
void searchAccount(Account accounts[], int count) {
  int number = getAccountNumber();
  int index = findAccount(accounts, count, number);

  if (index == -1) {
    cout << "\nNo account found with this number.\n";
    return;
  }

  cout << "\n========== SEARCH RESULT ==========\n";
  showAccount(accounts[index]);
}

// Update account information
void updateAccount(Account accounts[], int count) {
  int number = getAccountNumber();
  int index = findAccount(accounts, count, number);

  if (index == -1) {
    cout << "\nAccount not found.\n";
    return;
  }

  cout << "\nCurrent account information:\n";
  showAccount(accounts[index]);

  clearInput();

  cout << "\nEnter new customer name: ";
  getline(cin, accounts[index].name);

  cout << "Enter new CNIC/ID: ";
  getline(cin, accounts[index].cnic);

  cout << "Enter new phone number: ";
  getline(cin, accounts[index].phone);

  saveAccounts(accounts, count);

  cout << "\nAccount information updated successfully.\n";
}

// Delete an account
void deleteAccount(Account accounts[], int &count) {
  int number = getAccountNumber();
  int index = findAccount(accounts, count, number);

  if (index == -1) {
    cout << "\nAccount not found.\n";
    return;
  }

  for (int i = index; i < count - 1; i++) {
    accounts[i] = accounts[i + 1];
  }

  count--;
  saveAccounts(accounts, count);

  cout << "\nAccount deleted successfully.\n";
}

// Display all accounts
void displayAllAccounts(Account accounts[], int count) {
  if (count == 0) {
    cout << "\nNo accounts available.\n";
    return;
  }

  cout << "\n================ ALL ACCOUNTS ================\n";
  cout << left << setw(12) << "Account" << setw(22) << "Name" << setw(18)
       << "CNIC" << setw(16) << "Phone" << setw(12) << "Balance" << endl;

  cout << "-----------------------------------------------------------------\n";

  for (int i = 0; i < count; i++) {
    cout << left << setw(12) << accounts[i].accountNumber << setw(22)
         << accounts[i].name << setw(18) << accounts[i].cnic << setw(16)
         << accounts[i].phone << fixed << setprecision(2) << accounts[i].balance
         << endl;
  }

  cout << "\nTotal accounts: " << count << endl;
}

// Find an account and return its index
int findAccount(Account accounts[], int count, int number) {
  for (int i = 0; i < count; i++) {
    if (accounts[i].accountNumber == number) {
      return i;
    }
  }

  return -1;
}

// Display account information
void showAccount(Account acc) {
  cout << "Account Number : " << acc.accountNumber << endl;
  cout << "Customer Name  : " << acc.name << endl;
  cout << "CNIC/ID        : " << acc.cnic << endl;
  cout << "Phone Number   : " << acc.phone << endl;
  cout << "Balance        : " << fixed << setprecision(2) << acc.balance
       << endl;
}

// Get account number
int getAccountNumber() {
  int number;

  cout << "Enter account number: ";
  cin >> number;

  return number;
}

// Clear unwanted input
void clearInput() { cin.ignore(1000, '\n'); }

// Pause the screen
void pauseScreen() {
  cout << "\nPress Enter to continue...";
  cin.ignore(1000, '\n');
  cin.get();
}

// Main function
int main() {
  Account accounts[MAX_ACCOUNTS];
  int count = loadAccounts(accounts);
  int choice;

  do {
    cout << "\n\n============================================\n";
    cout << "          BANK MANAGEMENT SYSTEM\n";
    cout << "============================================\n";
    cout << "1. Create New Account\n";
    cout << "2. Display Account\n";
    cout << "3. Deposit Money\n";
    cout << "4. Withdraw Money\n";
    cout << "5. Search Account\n";
    cout << "6. Update Account\n";
    cout << "7. Delete Account\n";
    cout << "8. Display All Accounts\n";
    cout << "9. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      clearInput();
      choice = 0;
    }

    switch (choice) {
    case 1:
      createAccount(accounts, count);
      pauseScreen();
      break;

    case 2:
      displayAccount(accounts, count);
      pauseScreen();
      break;

    case 3:
      depositMoney(accounts, count);
      pauseScreen();
      break;

    case 4:
      withdrawMoney(accounts, count);
      pauseScreen();
      break;

    case 5:
      searchAccount(accounts, count);
      pauseScreen();
      break;

    case 6:
      updateAccount(accounts, count);
      pauseScreen();
      break;

    case 7:
      deleteAccount(accounts, count);
      pauseScreen();
      break;

    case 8:
      displayAllAccounts(accounts, count);
      pauseScreen();
      break;

    case 9:
      cout << "\nThank you for using Bank Management System.\n";
      break;

    default:
      cout << "\nInvalid choice. Please enter 1 to 9.\n";
      pauseScreen();
    }

  } while (choice != 9);

  return 0;
}
