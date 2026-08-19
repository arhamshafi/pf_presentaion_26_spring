
// Usaid Kanjra
// Faizan Nadeem
// Hassan Amir

#include <iomanip>
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;

string intToStr(int val) {
  ostringstream oss;
  oss << val;
  return oss.str();
}

const int CLR_DEFAULT = 7;
const int CLR_TITLE = 11;
const int CLR_MENU = 14;
const int CLR_SUCCESS = 10;
const int CLR_ERROR = 12;
const int CLR_HEADER = 9;
const int CLR_HIGH = 13;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(int color) { SetConsoleTextAttribute(hConsole, color); }

const int MAX_AREAS = 20;

string areaName[MAX_AREAS];
int population[MAX_AREAS];
int damageLevel[MAX_AREAS];
int childrenCount[MAX_AREAS];
int elderlyCount[MAX_AREAS];
int medicalNeed[MAX_AREAS];
double priorityScore[MAX_AREAS];

int totalAreas = 0;
bool priorityCalculated = false;

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
  setColor(CLR_TITLE);
  cout << "============================================\n";
  cout << "   Welcome to ReliefIQ - Disaster Relief System\n";
  cout << "============================================\n";
  setColor(CLR_DEFAULT);

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
      setColor(CLR_SUCCESS);
      cout << "\nExiting ReliefIQ. Stay safe!\n";
      setColor(CLR_DEFAULT);
      break;
    default:
      setColor(CLR_ERROR);
      cout << "\nInvalid choice, try again.\n";
      setColor(CLR_DEFAULT);
    }

  } while (choice != 7);

  return 0;
}

void showMenu() {
  setColor(CLR_MENU);
  cout << "\n--------- MAIN MENU ---------\n";
  cout << "1. Add Affected Area\n";
  cout << "2. View Areas\n";
  cout << "3. Calculate Priority Scores\n";
  cout << "4. Allocate Resources\n";
  cout << "5. Search Area\n";
  cout << "6. Display Highest Priority Area\n";
  cout << "7. Exit\n";
  setColor(CLR_DEFAULT);
  cout << "Enter choice: ";
}

void setupResourcePool() {
  setColor(CLR_HEADER);
  cout << "\nEnter available relief resources:\n";
  setColor(CLR_DEFAULT);
  cout << "Total Food Packs: ";
  cin >> totalFood;
  cout << "Total Water Bottles: ";
  cin >> totalWater;
  cout << "Total Medicine Kits: ";
  cin >> totalMedicine;
}

void addArea() {
  if (totalAreas >= MAX_AREAS) {
    setColor(CLR_ERROR);
    cout << "\nArea limit reached! Cannot add more.\n";
    setColor(CLR_DEFAULT);
    return;
  }

  int i = totalAreas;
  cin.ignore();

  setColor(CLR_HEADER);
  cout << "\n--- Add New Affected Area ---\n";
  setColor(CLR_DEFAULT);

  cout << "Area Name: ";
  getline(cin, areaName[i]);

  cout << "Population: ";
  cin >> population[i];

  int damage;
  do {
    cout << "Damage Level (1-100%): ";
    cin >> damage;
    if (damage < 1 || damage > 100) {
      setColor(CLR_ERROR);
      cout << "Invalid! Enter a value between 1 and 100.\n";
      setColor(CLR_DEFAULT);
    }
  } while (damage < 1 || damage > 100);
  damageLevel[i] = damage;

  int children, elderly;
  do {
    cout << "Children Count: ";
    cin >> children;
    cout << "Elderly Count: ";
    cin >> elderly;

    if (children + elderly > population[i]) {
      setColor(CLR_ERROR);
      cout << "Error: Children + Elderly (" << (children + elderly)
           << ") cannot exceed total Population (" << population[i]
           << "). Re-enter.\n";
      setColor(CLR_DEFAULT);
    }
  } while (children + elderly > population[i]);
  childrenCount[i] = children;
  elderlyCount[i] = elderly;

  int medNeed;
  do {
    cout << "Medical Need (1-100%): ";
    cin >> medNeed;
    if (medNeed < 1 || medNeed > 100) {
      setColor(CLR_ERROR);
      cout << "Invalid! Enter a value between 1 and 100.\n";
      setColor(CLR_DEFAULT);
    }
  } while (medNeed < 1 || medNeed > 100);
  medicalNeed[i] = medNeed;

  priorityScore[i] = 0;
  isAllocated[i] = false;

  totalAreas++;
  priorityCalculated = false;

  setColor(CLR_SUCCESS);
  cout << "\nArea \"" << areaName[i] << "\" added successfully!\n";
  setColor(CLR_DEFAULT);
}

void viewAreas() {
  if (totalAreas == 0) {
    setColor(CLR_ERROR);
    cout << "\nNo areas added yet.\n";
    setColor(CLR_DEFAULT);
    return;
  }

  setColor(CLR_HEADER);
  cout << "\n--- List of Affected Areas ---\n";
  cout << left << setw(15) << "Area" << setw(12) << "Population" << setw(10)
       << "Damage" << setw(10) << "Children" << setw(10) << "Elderly"
       << setw(12) << "MedNeed";
  if (priorityCalculated)
    cout << setw(12) << "Priority";
  cout << endl;
  setColor(CLR_DEFAULT);

  for (int i = 0; i < totalAreas; i++) {
    string damageStr = intToStr(damageLevel[i]) + "%";
    string medStr = intToStr(medicalNeed[i]) + "%";

    cout << left << setw(15) << areaName[i] << setw(12) << population[i]
         << setw(10) << damageStr << setw(10) << childrenCount[i] << setw(10)
         << elderlyCount[i] << setw(12) << medStr;
    if (priorityCalculated)
      cout << setw(12) << priorityScore[i];
    cout << endl;
  }
}

void calculatePriority() {
  if (totalAreas == 0) {
    setColor(CLR_ERROR);
    cout << "\nNo areas to calculate priority for.\n";
    setColor(CLR_DEFAULT);
    return;
  }

  for (int i = 0; i < totalAreas; i++) {
    priorityScore[i] = population[i] + (damageLevel[i] * 10) +
                       (medicalNeed[i] * 8) + (childrenCount[i] * 2) +
                       (elderlyCount[i] * 2);
  }

  priorityCalculated = true;
  sortByPriority();

  setColor(CLR_SUCCESS);
  cout << "\nPriority scores calculated and areas ranked!\n";
  setColor(CLR_DEFAULT);
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
    setColor(CLR_ERROR);
    cout << "\nNo areas available. Add areas first.\n";
    setColor(CLR_DEFAULT);
    return;
  }

  calculatePriority();

  int foodNeeded[MAX_AREAS];
  int waterNeeded[MAX_AREAS];
  int medNeeded[MAX_AREAS];
  long long totalFoodNeed = 0, totalWaterNeed = 0, totalMedNeed = 0;

  for (int i = 0; i < totalAreas; i++) {
    foodNeeded[i] = population[i];
    waterNeeded[i] = population[i] * 2;
    medNeeded[i] = (population[i] * medicalNeed[i]) / 1000;
    if (medNeeded[i] < 1)
      medNeeded[i] = 1;

    totalFoodNeed += foodNeeded[i];
    totalWaterNeed += waterNeeded[i];
    totalMedNeed += medNeeded[i];
  }

  int foodGiven[MAX_AREAS] = {0};
  int waterGiven[MAX_AREAS] = {0};
  int medGiven[MAX_AREAS] = {0};

  for (int i = 0; i < totalAreas; i++) {
    if (totalFoodNeed > 0) {
      foodGiven[i] =
          (totalFood >= totalFoodNeed)
              ? foodNeeded[i]
              : (int)((long long)totalFood * foodNeeded[i] / totalFoodNeed);
    }
    if (totalWaterNeed > 0) {
      waterGiven[i] =
          (totalWater >= totalWaterNeed)
              ? waterNeeded[i]
              : (int)((long long)totalWater * waterNeeded[i] / totalWaterNeed);
    }
    if (totalMedNeed > 0) {
      medGiven[i] =
          (totalMedicine >= totalMedNeed)
              ? medNeeded[i]
              : (int)((long long)totalMedicine * medNeeded[i] / totalMedNeed);
    }
  }

  int foodSumGiven = 0, waterSumGiven = 0, medSumGiven = 0;
  for (int i = 0; i < totalAreas; i++) {
    foodSumGiven += foodGiven[i];
    waterSumGiven += waterGiven[i];
    medSumGiven += medGiven[i];
  }

  int foodLeftover = min(totalFood, (int)totalFoodNeed) - foodSumGiven;
  int waterLeftover = min(totalWater, (int)totalWaterNeed) - waterSumGiven;
  int medLeftover = min(totalMedicine, (int)totalMedNeed) - medSumGiven;

  for (int i = 0; i < totalAreas && foodLeftover > 0; i++) {
    if (foodGiven[i] < foodNeeded[i]) {
      foodGiven[i]++;
      foodLeftover--;
    }
  }
  for (int i = 0; i < totalAreas && waterLeftover > 0; i++) {
    if (waterGiven[i] < waterNeeded[i]) {
      waterGiven[i]++;
      waterLeftover--;
    }
  }
  for (int i = 0; i < totalAreas && medLeftover > 0; i++) {
    if (medGiven[i] < medNeeded[i]) {
      medGiven[i]++;
      medLeftover--;
    }
  }

  setColor(CLR_HEADER);
  cout << "\n--- Allocating Resources (Proportional by Priority) ---\n";
  setColor(CLR_DEFAULT);

  for (int i = 0; i < totalAreas; i++) {
    allocatedFood[i] += foodGiven[i];
    allocatedWater[i] += waterGiven[i];
    allocatedMedicine[i] += medGiven[i];
    isAllocated[i] = (foodGiven[i] > 0 || waterGiven[i] > 0 || medGiven[i] > 0);

    totalFood -= foodGiven[i];
    totalWater -= waterGiven[i];
    totalMedicine -= medGiven[i];

    setColor(CLR_SUCCESS);
    cout << "\nArea: " << areaName[i]
         << " (Priority Score: " << priorityScore[i] << ")\n";
    setColor(CLR_DEFAULT);
    cout << "  Food Given:     " << foodGiven[i] << "\n";
    cout << "  Water Given:    " << waterGiven[i] << "\n";
    cout << "  Medicine Given: " << medGiven[i] << "\n";
  }

  setColor(CLR_HEADER);
  cout << "\n--- Remaining Resources ---\n";
  setColor(CLR_DEFAULT);
  cout << "Food: " << totalFood << " | Water: " << totalWater
       << " | Medicine: " << totalMedicine << endl;
}

void searchArea() {
  if (totalAreas == 0) {
    setColor(CLR_ERROR);
    cout << "\nNo areas added yet.\n";
    setColor(CLR_DEFAULT);
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
      setColor(CLR_HEADER);
      cout << "\n--- Area Found ---\n";
      setColor(CLR_DEFAULT);
      cout << "Name: " << areaName[i] << endl;
      cout << "Population: " << population[i] << endl;
      cout << "Damage Level: " << damageLevel[i] << "%" << endl;
      cout << "Children: " << childrenCount[i] << endl;
      cout << "Elderly: " << elderlyCount[i] << endl;
      cout << "Medical Need: " << medicalNeed[i] << "%" << endl;
      if (priorityCalculated)
        cout << "Priority Score: " << priorityScore[i] << endl;

      if (isAllocated[i]) {
        setColor(CLR_SUCCESS);
        cout << "Resources Allocated -> Food: " << allocatedFood[i]
             << ", Water: " << allocatedWater[i]
             << ", Medicine: " << allocatedMedicine[i] << endl;
        setColor(CLR_DEFAULT);
      } else {
        cout << "No resources allocated yet.\n";
      }
      break;
    }
  }

  if (!found) {
    setColor(CLR_ERROR);
    cout << "\nArea \"" << target << "\" not found.\n";
    setColor(CLR_DEFAULT);
  }
}

void displayHighestPriority() {
  if (totalAreas == 0) {
    setColor(CLR_ERROR);
    cout << "\nNo areas added yet.\n";
    setColor(CLR_DEFAULT);
    return;
  }

  calculatePriority();

  setColor(CLR_HIGH);
  cout << "\n--- HIGHEST PRIORITY AREA ---\n";
  cout << "Area: " << areaName[0] << endl;
  cout << "Priority Score: " << priorityScore[0] << endl;
  cout << "This area should receive relief FIRST.\n";
  setColor(CLR_DEFAULT);
}