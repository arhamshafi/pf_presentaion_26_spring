#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Maximum number of bills that can be stored
const int MAX_BILLS = 100;

// Structure for one electricity bill
struct Bill {
  int billNumber;
  string customerName;
  string meterNumber;
  string address;
  double previousReading;
  double currentReading;
  double units;
  double energyCharges;
  double fixedCharges;
  double tax;
  double totalBill;
};

// Function prototypes
int loadBills(Bill bills[]);
void saveBills(Bill bills[], int count);
void createBill(Bill bills[], int &count);
void displayBill(Bill bills[], int count);
void searchBill(Bill bills[], int count);
void updateBill(Bill bills[], int count);
void deleteBill(Bill bills[], int &count);
void displayAllBills(Bill bills[], int count);
int findBill(Bill bills[], int count, int number);
double calculateEnergyCharges(double units);
double calculateFixedCharges(double units);
double calculateTax(double energyCharges);
void calculateBillAmount(Bill &bill);
void showBill(Bill bill);
int getBillNumber();
void clearInput();
void pauseScreen();

// Load bills from a text file
int loadBills(Bill bills[]) {
  ifstream file("electricity_bills.txt");
  int count = 0;

  if (!file) {
    return 0;
  }

  while (count < MAX_BILLS) {
    string line;

    if (!(file >> bills[count].billNumber)) {
      break;
    }

    file.ignore(1000, '\n');

    getline(file, bills[count].customerName, '|');
    getline(file, bills[count].meterNumber, '|');
    getline(file, bills[count].address, '|');

    getline(file, line);
    bills[count].previousReading = atof(line.c_str());

    getline(file, line);
    bills[count].currentReading = atof(line.c_str());

    getline(file, line);
    bills[count].units = atof(line.c_str());

    getline(file, line);
    bills[count].energyCharges = atof(line.c_str());

    getline(file, line);
    bills[count].fixedCharges = atof(line.c_str());

    getline(file, line);
    bills[count].tax = atof(line.c_str());

    getline(file, line);
    bills[count].totalBill = atof(line.c_str());

    count++;
  }

  file.close();
  return count;
}

// Save all bills into a text file
void saveBills(Bill bills[], int count) {
  ofstream file("electricity_bills.txt");

  if (!file) {
    cout << "\nUnable to save bill data.\n";
    return;
  }

  for (int i = 0; i < count; i++) {
    file << bills[i].billNumber << endl;
    file << bills[i].customerName << "|";
    file << bills[i].meterNumber << "|";
    file << bills[i].address << "|" << endl;

    file << fixed << setprecision(2);
    file << bills[i].previousReading << endl;
    file << bills[i].currentReading << endl;
    file << bills[i].units << endl;
    file << bills[i].energyCharges << endl;
    file << bills[i].fixedCharges << endl;
    file << bills[i].tax << endl;
    file << bills[i].totalBill << endl;
  }

  file.close();
}

// Create a new electricity bill
void createBill(Bill bills[], int &count) {
  if (count >= MAX_BILLS) {
    cout << "\nBill storage is full.\n";
    return;
  }

  Bill bill;

  cout << "\n========== CREATE ELECTRICITY BILL ==========\n";

  cout << "Enter bill number: ";
  cin >> bill.billNumber;

  if (findBill(bills, count, bill.billNumber) != -1) {
    cout << "This bill number already exists.\n";
    return;
  }

  clearInput();

  cout << "Enter customer name: ";
  getline(cin, bill.customerName);

  cout << "Enter meter number: ";
  getline(cin, bill.meterNumber);

  cout << "Enter customer address: ";
  getline(cin, bill.address);

  cout << "Enter previous meter reading: ";
  cin >> bill.previousReading;

  cout << "Enter current meter reading: ";
  cin >> bill.currentReading;

  if (cin.fail()) {
    cin.clear();
    clearInput();
    cout << "Invalid meter reading entered.\n";
    return;
  }

  if (bill.previousReading < 0 || bill.currentReading < 0) {
    cout << "Meter readings cannot be negative.\n";
    return;
  }

  if (bill.currentReading < bill.previousReading) {
    cout << "Current reading cannot be less than previous reading.\n";
    return;
  }

  // Units consumed are calculated from meter readings
  bill.units = bill.currentReading - bill.previousReading;

  // Calculate complete bill
  calculateBillAmount(bill);

  bills[count] = bill;
  count++;

  saveBills(bills, count);

  cout << "\nElectricity bill created successfully!\n";
  showBill(bill);
}

// Calculate the complete bill
void calculateBillAmount(Bill &bill) {
  bill.energyCharges = calculateEnergyCharges(bill.units);
  bill.fixedCharges = calculateFixedCharges(bill.units);
  bill.tax = calculateTax(bill.energyCharges);

  bill.totalBill = bill.energyCharges + bill.fixedCharges + bill.tax;
}

// Calculate energy charges using example slabs
double calculateEnergyCharges(double units) {
  double charges = 0;

  // 1 to 100 units
  if (units <= 100) {
    charges = units * 10;
  }

  // 101 to 200 units
  else if (units <= 200) {
    charges = (100 * 10) + ((units - 100) * 15);
  }

  // 201 to 300 units
  else if (units <= 300) {
    charges = (100 * 10) + (100 * 15) + ((units - 200) * 20);
  }

  // 301 to 500 units
  else if (units <= 500) {
    charges = (100 * 10) + (100 * 15) + (100 * 20) + ((units - 300) * 25);
  }

  // More than 500 units
  else {
    charges = (100 * 10) + (100 * 15) + (100 * 20) + (200 * 25) +
              ((units - 500) * 30);
  }

  return charges;
}

// Calculate fixed charges
double calculateFixedCharges(double units) {
  if (units == 0) {
    return 0;
  }

  if (units <= 100) {
    return 100;
  }

  if (units <= 300) {
    return 200;
  }

  return 300;
}

// Calculate 5 percent tax
double calculateTax(double energyCharges) { return energyCharges * 0.05; }

// Display one bill
void displayBill(Bill bills[], int count) {
  int number = getBillNumber();
  int index = findBill(bills, count, number);

  if (index == -1) {
    cout << "\nBill not found.\n";
    return;
  }

  cout << "\n========== ELECTRICITY BILL ==========\n";
  showBill(bills[index]);
}

// Search a bill
void searchBill(Bill bills[], int count) {
  int number = getBillNumber();
  int index = findBill(bills, count, number);

  if (index == -1) {
    cout << "\nNo bill found with this number.\n";
    return;
  }

  cout << "\n========== SEARCH RESULT ==========\n";
  showBill(bills[index]);
}

// Update meter readings and recalculate bill
void updateBill(Bill bills[], int count) {
  int number = getBillNumber();
  int index = findBill(bills, count, number);

  if (index == -1) {
    cout << "\nBill not found.\n";
    return;
  }

  cout << "\nCurrent bill information:\n";
  showBill(bills[index]);

  cout << "\nEnter new previous meter reading: ";
  cin >> bills[index].previousReading;

  cout << "Enter new current meter reading: ";
  cin >> bills[index].currentReading;

  if (cin.fail()) {
    cin.clear();
    clearInput();
    cout << "Invalid reading entered.\n";
    return;
  }

  if (bills[index].previousReading < 0 || bills[index].currentReading < 0) {
    cout << "Meter readings cannot be negative.\n";
    return;
  }

  if (bills[index].currentReading < bills[index].previousReading) {
    cout << "Current reading cannot be less than previous reading.\n";
    return;
  }

  bills[index].units =
      bills[index].currentReading - bills[index].previousReading;

  calculateBillAmount(bills[index]);
  saveBills(bills, count);

  cout << "\nBill updated successfully!\n";
  showBill(bills[index]);
}

// Delete a bill
void deleteBill(Bill bills[], int &count) {
  int number = getBillNumber();
  int index = findBill(bills, count, number);

  if (index == -1) {
    cout << "\nBill not found.\n";
    return;
  }

  for (int i = index; i < count - 1; i++) {
    bills[i] = bills[i + 1];
  }

  count--;
  saveBills(bills, count);

  cout << "\nBill deleted successfully.\n";
}

// Display all bills
void displayAllBills(Bill bills[], int count) {
  if (count == 0) {
    cout << "\nNo electricity bills available.\n";
    return;
  }

  cout << "\n================ ALL ELECTRICITY BILLS ================\n";

  cout << left << setw(10) << "Bill No." << setw(20) << "Customer" << setw(15)
       << "Meter" << setw(12) << "Units" << setw(15) << "Total Bill" << endl;

  cout
      << "------------------------------------------------------------------\n";

  for (int i = 0; i < count; i++) {
    cout << left << setw(10) << bills[i].billNumber << setw(20)
         << bills[i].customerName << setw(15) << bills[i].meterNumber
         << setw(12) << fixed << setprecision(2) << bills[i].units << setw(15)
         << bills[i].totalBill << endl;
  }

  cout << "\nTotal bills: " << count << endl;
}

// Find bill index using bill number
int findBill(Bill bills[], int count, int number) {
  for (int i = 0; i < count; i++) {
    if (bills[i].billNumber == number) {
      return i;
    }
  }

  return -1;
}

// Show complete bill information
void showBill(Bill bill) {
  cout << "\n------------------------------------------\n";
  cout << "Bill Number       : " << bill.billNumber << endl;
  cout << "Customer Name     : " << bill.customerName << endl;
  cout << "Meter Number      : " << bill.meterNumber << endl;
  cout << "Address           : " << bill.address << endl;
  cout << "Previous Reading  : " << fixed << setprecision(2)
       << bill.previousReading << endl;
  cout << "Current Reading   : " << bill.currentReading << endl;
  cout << "Units Consumed    : " << bill.units << endl;
  cout << "Energy Charges    : Rs. " << bill.energyCharges << endl;
  cout << "Fixed Charges     : Rs. " << bill.fixedCharges << endl;
  cout << "Tax (5%)          : Rs. " << bill.tax << endl;
  cout << "------------------------------------------\n";
  cout << "TOTAL BILL        : Rs. " << bill.totalBill << endl;
  cout << "------------------------------------------\n";
}

// Get bill number
int getBillNumber() {
  int number;

  cout << "Enter bill number: ";
  cin >> number;

  return number;
}

// Clear unwanted input
void clearInput() { cin.ignore(1000, '\n'); }

// Pause screen
void pauseScreen() {
  cout << "\nPress Enter to continue...";
  cin.ignore(1000, '\n');
  cin.get();
}

// Main function
int main() {
  Bill bills[MAX_BILLS];
  int count = loadBills(bills);
  int choice;

  do {
    cout << "\n\n============================================\n";
    cout << "       ELECTRICITY BILL CALCULATOR\n";
    cout << "============================================\n";
    cout << "1. Create New Bill\n";
    cout << "2. Display Bill\n";
    cout << "3. Search Bill\n";
    cout << "4. Update Bill\n";
    cout << "5. Delete Bill\n";
    cout << "6. Display All Bills\n";
    cout << "7. Exit\n";
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
      createBill(bills, count);
      pauseScreen();
      break;

    case 2:
      displayBill(bills, count);
      pauseScreen();
      break;

    case 3:
      searchBill(bills, count);
      pauseScreen();
      break;

    case 4:
      updateBill(bills, count);
      pauseScreen();
      break;

    case 5:
      deleteBill(bills, count);
      pauseScreen();
      break;

    case 6:
      displayAllBills(bills, count);
      pauseScreen();
      break;

    case 7:
      cout << "\nThank you for using Electricity Bill Calculator.\n";
      break;

    default:
      cout << "\nInvalid choice. Please enter 1 to 7.\n";
      pauseScreen();
    }

  } while (choice != 7);

  return 0;
}