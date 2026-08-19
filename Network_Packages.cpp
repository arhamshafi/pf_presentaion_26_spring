
// Abudul-Rehman
// Fatima

// ( DUO )
//===================================

#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

// ============================================================
//              SIM PACKAGE MANAGEMENT SYSTEM
//              Procedural C++ Project - No OOP
// ============================================================

// Maximum packages available for each network
const int MAX_PACKAGES = 6;

// ------------------------------------------------------------
// Function Prototypes
// ------------------------------------------------------------

void showHeader();
void showMainMenu();

void showNetworks();
void showPackages(string packageNames[], string packageDetails[],
                  double packagePrices[], int packageCount);

int selectNetwork();

void loadJazzPackages(string packageNames[], string packageDetails[],
                      double packagePrices[], int &packageCount);

void loadTelenorPackages(string packageNames[], string packageDetails[],
                         double packagePrices[], int &packageCount);

void loadZongPackages(string packageNames[], string packageDetails[],
                      double packagePrices[], int &packageCount);

void loadUfonePackages(string packageNames[], string packageDetails[],
                       double packagePrices[], int &packageCount);

string getNetworkName(int networkChoice);

void checkBalance(double balance);

void purchasePackage(string packageNames[], string packageDetails[],
                     double packagePrices[], int packageCount, double &balance,
                     string networkName, int &purchasedPackages,
                     double &totalSpent);

void showAccountSummary(string networkName, double balance,
                        int purchasedPackages, double totalSpent);

// ============================================================
//                         MAIN
// ============================================================

int main() {
  // --------------------------------------------------------
  // Variables
  // --------------------------------------------------------

  int mainChoice = 0;
  int networkChoice = 0;

  double balance = 0.0;

  int purchasedPackages = 0;
  double totalSpent = 0.0;

  string networkName = "Not Selected";

  // Package arrays
  string packageNames[MAX_PACKAGES];
  string packageDetails[MAX_PACKAGES];
  double packagePrices[MAX_PACKAGES];

  int packageCount = 0;

  // --------------------------------------------------------
  // Welcome Screen
  // --------------------------------------------------------

  showHeader();

  // --------------------------------------------------------
  // Get Initial Balance
  // --------------------------------------------------------

  cout << "\nEnter your available balance (Rs): ";
  cin >> balance;

  while (cin.fail() || balance < 0) {
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Invalid amount! Please enter a valid balance: ";
    cin >> balance;
  }

  // --------------------------------------------------------
  // Main Program Loop
  // --------------------------------------------------------

  while (mainChoice != 7) {
    showMainMenu();

    cout << "Enter your choice (1-7): ";
    cin >> mainChoice;

    // Input validation
    while (cin.fail() || mainChoice < 1 || mainChoice > 7) {
      cin.clear();
      cin.ignore(1000, '\n');

      cout << "Invalid choice! Please enter 1-7: ";
      cin >> mainChoice;
    }

    // ====================================================
    // OPTION 1 - SELECT NETWORK
    // ====================================================

    if (mainChoice == 1) {
      networkChoice = selectNetwork();

      networkName = getNetworkName(networkChoice);

      // Load packages according to selected network
      if (networkChoice == 1) {
        loadJazzPackages(packageNames, packageDetails, packagePrices,
                         packageCount);
      } else if (networkChoice == 2) {
        loadTelenorPackages(packageNames, packageDetails, packagePrices,
                            packageCount);
      } else if (networkChoice == 3) {
        loadZongPackages(packageNames, packageDetails, packagePrices,
                         packageCount);
      } else if (networkChoice == 4) {
        loadUfonePackages(packageNames, packageDetails, packagePrices,
                          packageCount);
      }

      cout
          << "\n============================================================\n";
      cout << " Network Selected Successfully: " << networkName << "\n";
      cout << "============================================================\n";
    }

    // ====================================================
    // OPTION 2 - VIEW PACKAGES
    // ====================================================

    else if (mainChoice == 2) {
      if (networkChoice == 0) {
        cout << "\n[!] Please select a SIM network first.\n";
      } else {
        cout << "\n============================================================"
                "\n";
        cout << "                 " << networkName << " PACKAGES\n";
        cout
            << "============================================================\n";

        showPackages(packageNames, packageDetails, packagePrices, packageCount);
      }
    }

    // ====================================================
    // OPTION 3 - BUY PACKAGE
    // ====================================================

    else if (mainChoice == 3) {
      if (networkChoice == 0) {
        cout << "\n[!] Please select a SIM network first.\n";
      } else {
        purchasePackage(packageNames, packageDetails, packagePrices,
                        packageCount, balance, networkName, purchasedPackages,
                        totalSpent);
      }
    }

    // ====================================================
    // OPTION 4 - CHECK BALANCE
    // ====================================================

    else if (mainChoice == 4) {
      checkBalance(balance);
    }

    // ====================================================
    // OPTION 5 - ACCOUNT SUMMARY
    // ====================================================

    else if (mainChoice == 5) {
      showAccountSummary(networkName, balance, purchasedPackages, totalSpent);
    }

    // ====================================================
    // OPTION 6 - SHOW AVAILABLE NETWORKS
    // ====================================================

    else if (mainChoice == 6) {
      showNetworks();
    }

    // ====================================================
    // OPTION 7 - EXIT
    // ====================================================

    else if (mainChoice == 7) {
      cout
          << "\n============================================================\n";
      cout << "        Thank You For Using SIM Package System!\n";
      cout << "                 Program Terminated.\n";
      cout << "============================================================\n";
    }
  }

  return 0;
}

// ============================================================
//                    HEADER FUNCTION
// ============================================================

void showHeader() {
  cout << "\n";
  cout << "============================================================\n";
  cout << "          SIM PACKAGE MANAGEMENT SYSTEM\n";
  cout << "============================================================\n";
  cout << "       Jazz | Telenor | Zong | Ufone\n";
  cout << "============================================================\n";
  cout << "        Welcome to SIM Package Management System\n";
  cout << "============================================================\n";
}

// ============================================================
//                    MAIN MENU
// ============================================================

void showMainMenu() {
  cout << "\n\n";
  cout << "------------------------------------------------------------\n";
  cout << "                       MAIN MENU\n";
  cout << "------------------------------------------------------------\n";
  cout << "  1. Select SIM Network\n";
  cout << "  2. View Available Packages\n";
  cout << "  3. Buy / Activate Package\n";
  cout << "  4. Check Balance\n";
  cout << "  5. Account Summary\n";
  cout << "  6. View Available Networks\n";
  cout << "  7. Exit\n";
  cout << "------------------------------------------------------------\n";
}

// ============================================================
//                 SHOW NETWORKS
// ============================================================

void showNetworks() {
  cout << "\n============================================================\n";
  cout << "                 AVAILABLE SIM NETWORKS\n";
  cout << "============================================================\n";

  cout << "  1. Jazz\n";
  cout << "  2. Telenor\n";
  cout << "  3. Zong\n";
  cout << "  4. Ufone\n";

  cout << "============================================================\n";
}

// ============================================================
//                 SELECT NETWORK
// ============================================================

int selectNetwork() {
  int choice;

  showNetworks();

  cout << "\nSelect your network (1-4): ";
  cin >> choice;

  while (cin.fail() || choice < 1 || choice > 4) {
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Invalid network! Please select 1-4: ";
    cin >> choice;
  }

  return choice;
}

// ============================================================
//                 NETWORK NAME
// ============================================================

string getNetworkName(int networkChoice) {
  switch (networkChoice) {
  case 1:
    return "Jazz";

  case 2:
    return "Telenor";

  case 3:
    return "Zong";

  case 4:
    return "Ufone";

  default:
    return "Not Selected";
  }
}

// ============================================================
//                 JAZZ PACKAGES
// ============================================================

void loadJazzPackages(string packageNames[], string packageDetails[],
                      double packagePrices[], int &packageCount) {
  packageCount = 5;

  packageNames[0] = "Jazz Daily Basic";
  packageDetails[0] = "500 MB Internet + 100 Jazz Mins";
  packagePrices[0] = 25;

  packageNames[1] = "Jazz Daily Plus";
  packageDetails[1] = "1 GB Internet + 200 Jazz Mins";
  packagePrices[1] = 45;

  packageNames[2] = "Jazz Weekly";
  packageDetails[2] = "5 GB Internet + 1000 Jazz Mins";
  packagePrices[2] = 150;

  packageNames[3] = "Jazz Weekly Plus";
  packageDetails[3] = "10 GB Internet + 2000 Jazz Mins";
  packagePrices[3] = 250;

  packageNames[4] = "Jazz Monthly";
  packageDetails[4] = "20 GB Internet + 5000 Mins";
  packagePrices[4] = 550;
}

// ============================================================
//                 TELENOR PACKAGES
// ============================================================

void loadTelenorPackages(string packageNames[], string packageDetails[],
                         double packagePrices[], int &packageCount) {
  packageCount = 5;

  packageNames[0] = "Telenor Daily";
  packageDetails[0] = "500 MB Internet + 100 Mins";
  packagePrices[0] = 25;

  packageNames[1] = "Telenor Daily Plus";
  packageDetails[1] = "1 GB Internet + 200 Mins";
  packagePrices[1] = 45;

  packageNames[2] = "Telenor Weekly";
  packageDetails[2] = "5 GB Internet + 1000 Mins";
  packagePrices[2] = 150;

  packageNames[3] = "Telenor Weekly Plus";
  packageDetails[3] = "10 GB Internet + 2000 Mins";
  packagePrices[3] = 250;

  packageNames[4] = "Telenor Monthly";
  packageDetails[4] = "20 GB Internet + 5000 Mins";
  packagePrices[4] = 550;
}

// ============================================================
//                 ZONG PACKAGES
// ============================================================

void loadZongPackages(string packageNames[], string packageDetails[],
                      double packagePrices[], int &packageCount) {
  packageCount = 5;

  packageNames[0] = "Zong Daily";
  packageDetails[0] = "500 MB Internet + 100 Zong Mins";
  packagePrices[0] = 25;

  packageNames[1] = "Zong Daily Plus";
  packageDetails[1] = "1 GB Internet + 200 Zong Mins";
  packagePrices[1] = 45;

  packageNames[2] = "Zong Weekly";
  packageDetails[2] = "5 GB Internet + 1000 Zong Mins";
  packagePrices[2] = 150;

  packageNames[3] = "Zong Weekly Plus";
  packageDetails[3] = "10 GB Internet + 2000 Zong Mins";
  packagePrices[3] = 250;

  packageNames[4] = "Zong Monthly";
  packageDetails[4] = "20 GB Internet + 5000 Mins";
  packagePrices[4] = 550;
}

// ============================================================
//                 UFONE PACKAGES
// ============================================================

void loadUfonePackages(string packageNames[], string packageDetails[],
                       double packagePrices[], int &packageCount) {
  packageCount = 5;

  packageNames[0] = "Ufone Daily";
  packageDetails[0] = "500 MB Internet + 100 Ufone Mins";
  packagePrices[0] = 25;

  packageNames[1] = "Ufone Daily Plus";
  packageDetails[1] = "1 GB Internet + 200 Ufone Mins";
  packagePrices[1] = 45;

  packageNames[2] = "Ufone Weekly";
  packageDetails[2] = "5 GB Internet + 1000 Ufone Mins";
  packagePrices[2] = 150;

  packageNames[3] = "Ufone Weekly Plus";
  packageDetails[3] = "10 GB Internet + 2000 Ufone Mins";
  packagePrices[3] = 250;

  packageNames[4] = "Ufone Monthly";
  packageDetails[4] = "20 GB Internet + 5000 Mins";
  packagePrices[4] = 550;
}

// ============================================================
//                 SHOW PACKAGES
// ============================================================

void showPackages(string packageNames[], string packageDetails[],
                  double packagePrices[], int packageCount) {
  cout << "\n";
  cout << left << setw(5) << "No." << setw(25) << "Package" << setw(42)
       << "Package Details"
       << "Price\n";

  cout << "--------------------------------------------------------------------"
          "-\n";

  for (int i = 0; i < packageCount; i++) {
    cout << left << setw(5) << i + 1 << setw(25) << packageNames[i] << setw(42)
         << packageDetails[i] << "Rs. " << fixed << setprecision(0)
         << packagePrices[i] << "\n";
  }

  cout << "--------------------------------------------------------------------"
          "-\n";
}

// ============================================================
//                 CHECK BALANCE
// ============================================================

void checkBalance(double balance) {
  cout << "\n============================================================\n";
  cout << "                     BALANCE DETAILS\n";
  cout << "============================================================\n";

  cout << "Available Balance : Rs. " << fixed << setprecision(2) << balance
       << "\n";

  cout << "============================================================\n";
}

// ============================================================
//                 PURCHASE PACKAGE
// ============================================================

void purchasePackage(string packageNames[], string packageDetails[],
                     double packagePrices[], int packageCount, double &balance,
                     string networkName, int &purchasedPackages,
                     double &totalSpent) {
  int packageChoice;

  cout << "\n============================================================\n";
  cout << "                  PACKAGE ACTIVATION\n";
  cout << "============================================================\n";

  cout << "Selected Network : " << networkName << "\n";
  cout << "Current Balance  : Rs. " << fixed << setprecision(2) << balance
       << "\n";

  showPackages(packageNames, packageDetails, packagePrices, packageCount);

  cout << "\nEnter package number to activate (1-" << packageCount << "): ";

  cin >> packageChoice;

  while (cin.fail() || packageChoice < 1 || packageChoice > packageCount) {
    cin.clear();
    cin.ignore(1000, '\n');

    cout << "Invalid package! Please enter 1-" << packageCount << ": ";

    cin >> packageChoice;
  }

  int index = packageChoice - 1;

  double packagePrice = packagePrices[index];

  cout << "\n------------------------------------------------------------\n";
  cout << "Selected Package : " << packageNames[index] << "\n";
  cout << "Package Details  : " << packageDetails[index] << "\n";
  cout << "Package Price    : Rs. " << packagePrice << "\n";
  cout << "Your Balance     : Rs. " << balance << "\n";
  cout << "------------------------------------------------------------\n";

  // --------------------------------------------------------
  // Check Balance
  // --------------------------------------------------------

  if (balance >= packagePrice) {
    balance = balance - packagePrice;

    purchasedPackages++;
    totalSpent += packagePrice;

    cout << "\n";
    cout << "============================================================\n";
    cout << "             PACKAGE ACTIVATED SUCCESSFULLY!\n";
    cout << "============================================================\n";

    cout << "Network          : " << networkName << "\n";
    cout << "Package          : " << packageNames[index] << "\n";
    cout << "Price Deducted   : Rs. " << packagePrice << "\n";
    cout << "Remaining Balance: Rs. " << fixed << setprecision(2) << balance
         << "\n";

    cout << "============================================================\n";
  } else {
    double requiredAmount = packagePrice - balance;

    cout << "\n";
    cout << "============================================================\n";
    cout << "              INSUFFICIENT BALANCE!\n";
    cout << "============================================================\n";

    cout << "Package Price    : Rs. " << packagePrice << "\n";

    cout << "Available Balance: Rs. " << balance << "\n";

    cout << "Additional Amount: Rs. " << requiredAmount << "\n";

    cout << "\n[!] Package was NOT activated.\n";

    cout << "============================================================\n";
  }
}

// ============================================================
//                 ACCOUNT SUMMARY
// ============================================================

void showAccountSummary(string networkName, double balance,
                        int purchasedPackages, double totalSpent) {
  cout << "\n============================================================\n";
  cout << "                    ACCOUNT SUMMARY\n";
  cout << "============================================================\n";

  cout << left;
  cout << setw(25) << "Selected Network"
       << ": " << networkName << "\n";

  cout << setw(25) << "Current Balance"
       << ": Rs. " << fixed << setprecision(2) << balance << "\n";

  cout << setw(25) << "Packages Activated"
       << ": " << purchasedPackages << "\n";

  cout << setw(25) << "Total Amount Spent"
       << ": Rs. " << totalSpent << "\n";

  cout << "============================================================\n";

  if (purchasedPackages == 0) {
    cout << "No package has been activated yet.\n";
  } else {
    cout << "Account Status: ACTIVE\n";
  }

  cout << "============================================================\n";
}