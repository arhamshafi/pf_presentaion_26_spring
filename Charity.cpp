
// Usaid Kanjra
// Faizan Nadeem
// Hassan Amir

// =============================

#include <iomanip>
#include <iostream>

using namespace std;

const int MAX_AREAS = 20;

string areaName[MAX_AREAS];
int population[MAX_AREAS];
int damageLevel[MAX_AREAS];
int childrenCount[MAX_AREAS];
int elderlyCount[MAX_AREAS];
int medicalNeed[MAX_AREAS];
double priorityScore[MAX_AREAS];

int totalAreas = 0;

int totalFood = 0;
int totalWater = 0;
int totalMedicine = 0;

int allocatedFood[MAX_AREAS] = {0};
int allocatedWater[MAX_AREAS] = {0};
int allocatedMedicine[MAX_AREAS] = {0};
bool isAllocated[MAX_AREAS] = {false};

void showMenu();
void addArea();
void viewAreas();
void calculatePriority();
void sortByPriority();
void allocateResources();
void searchArea();
void displayHighestPriority();
void setupResourcePool();

int main() {
  cout << "============================================\n";
  cout << "   Welcome to ReliefIQ - Disaster Relief System\n";
  cout << "============================================\n";

  setupResourcePool();

  int choice;
  do {
    showMenu();
    cin >> choice;

    switch (choice) {
    case 1:
      addArea();
      break;
    case 2:
      viewAreas();
      break;
    case 3:
      calculatePriority();
      break;
    case 4:
      allocateResources();
      break;
    case 5:
      searchArea();
      break;
    case 6:
      displayHighestPriority();
      break;
    case 7:
      cout << "\nExiting ReliefIQ. Stay safe!\n";
      break;
    default:
      cout << "\nInvalid choice, try again.\n";
    }

  } while (choice != 7);

  return 0;
}

void showMenu() {
  cout << "\n--------- MAIN MENU ---------\n";
  cout << "1. Add Affected Area\n";
  cout << "2. View Areas\n";
  cout << "3. Calculate Priority Scores\n";
  cout << "4. Allocate Resources\n";
  cout << "5. Search Area\n";
  cout << "6. Display Highest Priority Area\n";
  cout << "7. Exit\n";
  cout << "Enter choice: ";
}

void setupResourcePool() {
  cout << "\nEnter available relief resources:\n";
  cout << "Total Food Packs: ";
  cin >> totalFood;
  cout << "Total Water Bottles: ";
  cin >> totalWater;
  cout << "Total Medicine Kits: ";
  cin >> totalMedicine;
}

void addArea() {
  if (totalAreas >= MAX_AREAS) {
    cout << "\nArea limit reached! Cannot add more.\n";
    return;
  }

  int i = totalAreas;
  cin.ignore();

  cout << "\n--- Add New Affected Area ---\n";
  cout << "Area Name: ";
  getline(cin, areaName[i]);

  cout << "Population: ";
  cin >> population[i];

  cout << "Damage Level (1-10): ";
  cin >> damageLevel[i];

  cout << "Children Count: ";
  cin >> childrenCount[i];

  cout << "Elderly Count: ";
  cin >> elderlyCount[i];

  cout << "Medical Need (1-10): ";
  cin >> medicalNeed[i];

  priorityScore[i] = 0;
  isAllocated[i] = false;

  totalAreas++;
  cout << "\nArea \"" << areaName[i] << "\" added successfully!\n";
}

void viewAreas() {
  if (totalAreas == 0) {
    cout << "\nNo areas added yet.\n";
    return;
  }

  cout << "\n--- List of Affected Areas ---\n";
  cout << left << setw(15) << "Area" << setw(12) << "Population" << setw(10)
       << "Damage" << setw(10) << "Children" << setw(10) << "Elderly"
       << setw(12) << "MedNeed" << setw(10) << "Priority" << endl;

  for (int i = 0; i < totalAreas; i++) {
    cout << left << setw(15) << areaName[i] << setw(12) << population[i]
         << setw(10) << damageLevel[i] << setw(10) << childrenCount[i]
         << setw(10) << elderlyCount[i] << setw(12) << medicalNeed[i]
         << setw(10) << priorityScore[i] << endl;
  }
}

void calculatePriority() {
  if (totalAreas == 0) {
    cout << "\nNo areas to calculate priority for.\n";
    return;
  }

  for (int i = 0; i < totalAreas; i++) {
    priorityScore[i] = population[i] + (damageLevel[i] * 100) +
                       (medicalNeed[i] * 80) + (childrenCount[i] * 2) +
                       (elderlyCount[i] * 2);
  }

  sortByPriority();

  cout << "\nPriority scores calculated and areas ranked!\n";
  viewAreas();
}

void sortByPriority() {
  for (int i = 0; i < totalAreas - 1; i++) {
    int maxIndex = i;

    for (int j = i + 1; j < totalAreas; j++) {
      if (priorityScore[j] > priorityScore[maxIndex]) {
        maxIndex = j;
      }
    }

    if (maxIndex != i) {

      swap(areaName[i], areaName[maxIndex]);
      swap(population[i], population[maxIndex]);
      swap(damageLevel[i], damageLevel[maxIndex]);
      swap(childrenCount[i], childrenCount[maxIndex]);
      swap(elderlyCount[i], elderlyCount[maxIndex]);
      swap(medicalNeed[i], medicalNeed[maxIndex]);
      swap(priorityScore[i], priorityScore[maxIndex]);
      swap(allocatedFood[i], allocatedFood[maxIndex]);
      swap(allocatedWater[i], allocatedWater[maxIndex]);
      swap(allocatedMedicine[i], allocatedMedicine[maxIndex]);
      swap(isAllocated[i], isAllocated[maxIndex]);
    }
  }
}

void allocateResources() {
  if (totalAreas == 0) {
    cout << "\nNo areas available. Add areas first.\n";
    return;
  }

  calculatePriority();

  const int FOOD_PER_AREA = 100;
  const int WATER_PER_AREA = 150;
  const int MEDICINE_PER_AREA = 40;

  cout << "\n--- Allocating Resources (Highest Priority First) ---\n";

  for (int i = 0; i < totalAreas; i++) {
    if (totalFood <= 0 && totalWater <= 0 && totalMedicine <= 0) {
      cout << "\nAll resources have been fully distributed.\n";
      break;
    }

    int foodGiven = min(FOOD_PER_AREA, totalFood);
    int waterGiven = min(WATER_PER_AREA, totalWater);
    int medGiven = min(MEDICINE_PER_AREA, totalMedicine);

    allocatedFood[i] += foodGiven;
    allocatedWater[i] += waterGiven;
    allocatedMedicine[i] += medGiven;
    isAllocated[i] = true;

    totalFood -= foodGiven;
    totalWater -= waterGiven;
    totalMedicine -= medGiven;

    cout << "\nArea: " << areaName[i]
         << " (Priority Score: " << priorityScore[i] << ")\n";
    cout << "  Food Given:     " << foodGiven << "\n";
    cout << "  Water Given:    " << waterGiven << "\n";
    cout << "  Medicine Given: " << medGiven << "\n";
  }

  cout << "\n--- Remaining Resources ---\n";
  cout << "Food: " << totalFood << " | Water: " << totalWater
       << " | Medicine: " << totalMedicine << endl;
}

void searchArea() {
  if (totalAreas == 0) {
    cout << "\nNo areas added yet.\n";
    return;
  }

  string target;
  cin.ignore();
  cout << "\nEnter area name to search: ";
  getline(cin, target);

  bool found = false;
  for (int i = 0; i < totalAreas; i++) {
    if (areaName[i] == target) {
      found = true;
      cout << "\n--- Area Found ---\n";
      cout << "Name: " << areaName[i] << endl;
      cout << "Population: " << population[i] << endl;
      cout << "Damage Level: " << damageLevel[i] << endl;
      cout << "Children: " << childrenCount[i] << endl;
      cout << "Elderly: " << elderlyCount[i] << endl;
      cout << "Medical Need: " << medicalNeed[i] << endl;
      cout << "Priority Score: " << priorityScore[i] << endl;

      if (isAllocated[i]) {
        cout << "Resources Allocated -> Food: " << allocatedFood[i]
             << ", Water: " << allocatedWater[i]
             << ", Medicine: " << allocatedMedicine[i] << endl;
      } else {
        cout << "No resources allocated yet.\n";
      }
      break;
    }
  }

  if (!found) {
    cout << "\nArea \"" << target << "\" not found.\n";
  }
}

void displayHighestPriority() {
  if (totalAreas == 0) {
    cout << "\nNo areas added yet.\n";
    return;
  }

  calculatePriority();

  cout << "\n--- HIGHEST PRIORITY AREA ---\n";
  cout << "Area: " << areaName[0] << endl;
  cout << "Priority Score: " << priorityScore[0] << endl;
  cout << "This area should receive relief FIRST.\n";
}