// Abu-Bakar Azhar
// Rabia

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// =====================================================
//                 FUNCTION PROTOTYPES
// =====================================================

void displayTitle();
void displayMenu();

void showStatus(int health, int energy, int hunger, int happiness, int coins,
                int day, string name);

void feedTiger(int &health, int &energy, int &hunger, int &happiness, int &meat,
               int &fish);

void playTiger(int &energy, int &happiness, int &hunger, int &coins, int &toys);

void sleepTiger(int &energy, int &hunger, int &happiness);

void giveWater(int &energy, int &happiness, int &water);

void bathTiger(int &happiness);

void exerciseTiger(int &energy, int &happiness, int &hunger);

void walkTiger(int &energy, int &happiness, int &hunger);

void giveMedicine(int &health, int &medicine, int &happiness);

void shop(int &coins, int &meat, int &fish, int &medicine, int &water,
          int &toys);

void showInventory(int meat, int fish, int medicine, int water, int toys);

void miniGame(int &coins, int &happiness);

void updateTiger(int &health, int &hunger, int &happiness);

void randomEvent(int &health, int &energy, int &hunger, int &happiness,
                 int &coins);

void nextDay(int &day, int &health, int &energy, int &hunger, int &happiness,
             int &coins);

void progressBar(int value);

void checkAchievements(int health, int energy, int hunger, int happiness,
                       int coins, int day);

void showTiger();

void pauseGame();

// =====================================================
//                     MAIN FUNCTION
// =====================================================

int main() {
  srand(time(0));

  string tigerName;

  // Initial Tiger Status
  int health = 80;
  int energy = 70;
  int hunger = 40;
  int happiness = 80;

  // Resources
  int coins = 100;
  int meat = 3;
  int fish = 2;
  int medicine = 2;
  int water = 5;
  int toys = 1;

  // Day
  int day = 1;

  int choice;
  bool running = true;

  // Start Game
  displayTitle();

  cout << "\nEnter your tiger's name: ";
  cin >> tigerName;

  cout << "\n====================================\n";
  cout << "Welcome, " << tigerName << "!\n";
  cout << "Take good care of your tiger.\n";
  cout << "====================================\n";

  // =================================================
  //                    GAME LOOP
  // =================================================

  while (running) {
    displayMenu();

    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
      // =================================================
      // FEED
      // =================================================

    case 1:

      feedTiger(health, energy, hunger, happiness, meat, fish);

      updateTiger(health, hunger, happiness);

      break;

      // =================================================
      // PLAY
      // =================================================

    case 2:

      playTiger(energy, happiness, hunger, coins, toys);

      updateTiger(health, hunger, happiness);

      break;

      // =================================================
      // SLEEP
      // =================================================

    case 3:

      sleepTiger(energy, hunger, happiness);

      updateTiger(health, hunger, happiness);

      break;

      // =================================================
      // WATER
      // =================================================

    case 4:

      giveWater(energy, happiness, water);

      updateTiger(health, hunger, happiness);

      break;

      // =================================================
      // BATH
      // =================================================

    case 5:

      bathTiger(happiness);

      updateTiger(health, hunger, happiness);

      break;

      // =================================================
      // EXERCISE
      // =================================================

    case 6:

      exerciseTiger(energy, happiness, hunger);

      updateTiger(health, hunger, happiness);

      break;

      // =================================================
      // WALK
      // =================================================

    case 7:

      walkTiger(energy, happiness, hunger);

      updateTiger(health, hunger, happiness);

      break;

      // =================================================
      // MEDICINE
      // =================================================

    case 8:

      giveMedicine(health, medicine, happiness);

      updateTiger(health, hunger, happiness);

      break;

      // =================================================
      // SHOP
      // =================================================

    case 9:

      shop(coins, meat, fish, medicine, water, toys);

      break;

      // =================================================
      // INVENTORY
      // =================================================

    case 10:

      showInventory(meat, fish, medicine, water, toys);

      break;

      // =================================================
      // MINI GAME
      // =================================================

    case 11:

      miniGame(coins, happiness);

      break;

      // =================================================
      // STATUS
      // =================================================

    case 12:

      showStatus(health, energy, hunger, happiness, coins, day, tigerName);

      break;

      // =================================================
      // NEXT DAY
      // =================================================

    case 13:

      nextDay(day, health, energy, hunger, happiness, coins);

      break;

      // =================================================
      // TIGER
      // =================================================

    case 14:

      showTiger();

      break;

      // =================================================
      // EXIT
      // =================================================

    case 15:

      cout << "\n====================================\n";
      cout << "       THANK YOU FOR PLAYING!\n";
      cout << "====================================\n";

      cout << "Your tiger " << tigerName << " will miss you!\n";

      running = false;

      break;

      // =================================================
      // INVALID
      // =================================================

    default:

      cout << "\nInvalid choice!\n";
      cout << "Please enter a number from 1 to 15.\n";

      break;
    }

    // =================================================
    // GAME OVER
    // =================================================

    if (health <= 0) {
      cout << "\n====================================\n";
      cout << "             GAME OVER\n";
      cout << "====================================\n";

      cout << "Your tiger became very sick.\n";

      running = false;
    }
  }

  return 0;
}

// =====================================================
//                    TITLE FUNCTION
// =====================================================

void displayTitle() {
  cout << "\n";
  cout << "=============================================\n";
  cout << "          TIGER VIRTUAL PET GAME\n";
  cout << "=============================================\n";
  cout << "       FEED - PLAY - CARE - SURVIVE\n";
  cout << "=============================================\n";
}

// =====================================================
//                    MENU FUNCTION
// =====================================================

void displayMenu() {
  cout << "\n";
  cout << "=============================================\n";
  cout << "                 MAIN MENU\n";
  cout << "=============================================\n";

  cout << "1.  Feed Tiger\n";
  cout << "2.  Play with Tiger\n";
  cout << "3.  Sleep\n";
  cout << "4.  Give Water\n";
  cout << "5.  Give Bath\n";
  cout << "6.  Exercise\n";
  cout << "7.  Go for Walk\n";
  cout << "8.  Give Medicine\n";
  cout << "9.  Visit Shop\n";
  cout << "10. Check Inventory\n";
  cout << "11. Play Mini Game\n";
  cout << "12. Check Status\n";
  cout << "13. Start Next Day\n";
  cout << "14. View Tiger\n";
  cout << "15. Exit Game\n";

  cout << "=============================================\n";
}

// =====================================================
//                    FEED FUNCTION
// =====================================================

void feedTiger(int &health, int &energy, int &hunger, int &happiness, int &meat,
               int &fish) {
  int choice;

  cout << "\n";
  cout << "====================================\n";
  cout << "             FEED TIGER\n";
  cout << "====================================\n";

  cout << "1. Meat\n";
  cout << "2. Fish\n";
  cout << "3. Cancel\n";

  cout << "Choose food: ";
  cin >> choice;

  if (choice == 1) {
    if (meat <= 0) {
      cout << "\nNo meat available.\n";
      return;
    }

    meat--;

    // Feed reduces hunger
    hunger -= 30;

    // Food gives small benefits
    health += 5;
    energy += 5;
    happiness += 5;

    cout << "\nTiger ate the meat!\n";
    cout << "Hunger decreased by 30.\n";
  }

  else if (choice == 2) {
    if (fish <= 0) {
      cout << "\nNo fish available.\n";
      return;
    }

    fish--;

    // Feed reduces hunger
    hunger -= 25;

    health += 5;
    energy += 5;
    happiness += 8;

    cout << "\nTiger ate the fish!\n";
    cout << "Hunger decreased by 25.\n";
  }

  else if (choice == 3) {
    cout << "\nFeed cancelled.\n";
    return;
  }

  else {
    cout << "\nInvalid choice.\n";
    return;
  }

  if (hunger < 0)
    hunger = 0;

  if (health > 100)
    health = 100;

  if (energy > 100)
    energy = 100;

  if (happiness > 100)
    happiness = 100;

  cout << "Tiger is feeling better!\n";
}

// =====================================================
//                    PLAY FUNCTION
// =====================================================

void playTiger(int &energy, int &happiness, int &hunger, int &coins,
               int &toys) {
  if (energy < 20) {
    cout << "\nTiger is too tired to play.\n";
    cout << "Let the tiger sleep first.\n";

    return;
  }

  int choice;

  cout << "\n";
  cout << "====================================\n";
  cout << "              PLAY TIME\n";
  cout << "====================================\n";

  cout << "1. Play Ball\n";
  cout << "2. Play with Toy\n";
  cout << "3. Chase Game\n";

  cout << "Choose game: ";
  cin >> choice;

  if (choice == 1) {
    cout << "\nYou played ball with the tiger.\n";

    happiness += 15;
    energy -= 15;
    hunger += 10;

    coins += 5;
  }

  else if (choice == 2) {
    if (toys <= 0) {
      cout << "\nYou don't have a toy.\n";
      return;
    }

    toys--;

    happiness += 20;
    energy -= 20;
    hunger += 12;

    coins += 10;

    cout << "\nTiger enjoyed playing with the toy!\n";
  }

  else if (choice == 3) {
    cout << "\nTiger is chasing around!\n";

    happiness += 25;
    energy -= 25;
    hunger += 15;

    coins += 15;
  }

  else {
    cout << "\nInvalid choice.\n";
    return;
  }

  if (happiness > 100)
    happiness = 100;

  if (energy < 0)
    energy = 0;

  if (hunger > 100)
    hunger = 100;

  cout << "Play session completed.\n";
}

// =====================================================
//                    SLEEP FUNCTION
// =====================================================

void sleepTiger(int &energy, int &hunger, int &happiness) {
  cout << "\n";
  cout << "====================================\n";
  cout << "          TIGER IS SLEEPING\n";
  cout << "====================================\n";

  cout << "Zzz... Zzz... Zzz...\n";

  energy += 40;
  hunger += 10;
  happiness += 5;

  if (energy > 100)
    energy = 100;

  if (hunger > 100)
    hunger = 100;

  if (happiness > 100)
    happiness = 100;

  cout << "\nTiger finished sleeping.\n";
}

// =====================================================
//                    WATER FUNCTION
// =====================================================

void giveWater(int &energy, int &happiness, int &water) {
  if (water <= 0) {
    cout << "\nNo water available.\n";
    cout << "Buy water from the shop.\n";

    return;
  }

  water--;

  energy += 10;
  happiness += 5;

  if (energy > 100)
    energy = 100;

  if (happiness > 100)
    happiness = 100;

  cout << "\nTiger drank fresh water.\n";
  cout << "Tiger feels refreshed!\n";
}

// =====================================================
//                    BATH FUNCTION
// =====================================================

void bathTiger(int &happiness) {
  cout << "\n";
  cout << "====================================\n";
  cout << "              BATH TIME\n";
  cout << "====================================\n";

  cout << "Cleaning tiger...\n";
  cout << "Washing tiger...\n";
  cout << "Drying tiger...\n";

  happiness += 15;

  if (happiness > 100)
    happiness = 100;

  cout << "\nTiger is clean and happy!\n";
}

// =====================================================
//                  EXERCISE FUNCTION
// =====================================================

void exerciseTiger(int &energy, int &happiness, int &hunger) {
  if (energy < 25) {
    cout << "\nTiger doesn't have enough energy.\n";
    cout << "Let the tiger rest first.\n";

    return;
  }

  cout << "\n";
  cout << "====================================\n";
  cout << "             EXERCISE\n";
  cout << "====================================\n";

  cout << "Tiger is exercising...\n";

  // Exercise does NOT increase health
  energy -= 25;

  // Exercise increases hunger
  hunger += 15;

  // Exercise increases happiness
  happiness += 10;

  if (energy < 0)
    energy = 0;

  if (hunger > 100)
    hunger = 100;

  if (happiness > 100)
    happiness = 100;

  cout << "\nExercise completed!\n";
  cout << "Energy decreased by 25.\n";
  cout << "Hunger increased by 15.\n";
  cout << "Happiness increased by 10.\n";
}

// =====================================================
//                    WALK FUNCTION
// =====================================================

void walkTiger(int &energy, int &happiness, int &hunger) {
  if (energy < 15) {
    cout << "\nTiger is too tired for a walk.\n";
    return;
  }

  cout << "\n";
  cout << "====================================\n";
  cout << "             WALK TIME\n";
  cout << "====================================\n";

  cout << "You went for a walk with your tiger.\n";

  energy -= 15;
  happiness += 15;
  hunger += 10;

  if (energy < 0)
    energy = 0;

  if (happiness > 100)
    happiness = 100;

  if (hunger > 100)
    hunger = 100;

  cout << "The walk was enjoyable!\n";
}

// =====================================================
//                  MEDICINE FUNCTION
// =====================================================

void giveMedicine(int &health, int &medicine, int &happiness) {
  if (medicine <= 0) {
    cout << "\nNo medicine available.\n";
    cout << "Buy medicine from the shop.\n";

    return;
  }

  if (health >= 90) {
    cout << "\nTiger doesn't need medicine right now.\n";
    return;
  }

  medicine--;

  health += 30;
  happiness += 5;

  if (health > 100)
    health = 100;

  if (happiness > 100)
    happiness = 100;

  cout << "\nMedicine given successfully.\n";
  cout << "Tiger is feeling better!\n";
}

// =====================================================
//                    SHOP FUNCTION
// =====================================================

void shop(int &coins, int &meat, int &fish, int &medicine, int &water,
          int &toys) {
  int choice;

  bool shopping = true;

  while (shopping) {
    cout << "\n";
    cout << "====================================\n";
    cout << "                SHOP\n";
    cout << "====================================\n";

    cout << "Your Coins: " << coins << "\n\n";

    cout << "1. Meat       - 20 Coins\n";
    cout << "2. Fish       - 15 Coins\n";
    cout << "3. Medicine   - 30 Coins\n";
    cout << "4. Water      - 10 Coins\n";
    cout << "5. Toy        - 40 Coins\n";
    cout << "6. Exit Shop\n";

    cout << "Choose item: ";
    cin >> choice;

    switch (choice) {
    case 1:

      if (coins >= 20) {
        coins -= 20;
        meat++;

        cout << "Meat purchased!\n";
      } else {
        cout << "Not enough coins.\n";
      }

      break;

    case 2:

      if (coins >= 15) {
        coins -= 15;
        fish++;

        cout << "Fish purchased!\n";
      } else {
        cout << "Not enough coins.\n";
      }

      break;

    case 3:

      if (coins >= 30) {
        coins -= 30;
        medicine++;

        cout << "Medicine purchased!\n";
      } else {
        cout << "Not enough coins.\n";
      }

      break;

    case 4:

      if (coins >= 10) {
        coins -= 10;
        water += 2;

        cout << "2 Water bottles purchased!\n";
      } else {
        cout << "Not enough coins.\n";
      }

      break;

    case 5:

      if (coins >= 40) {
        coins -= 40;
        toys++;

        cout << "Toy purchased!\n";
      } else {
        cout << "Not enough coins.\n";
      }

      break;

    case 6:

      shopping = false;

      cout << "Leaving shop...\n";

      break;

    default:

      cout << "Invalid shop choice.\n";
    }
  }
}

// =====================================================
//                  INVENTORY FUNCTION
// =====================================================

void showInventory(int meat, int fish, int medicine, int water, int toys) {
  cout << "\n";
  cout << "====================================\n";
  cout << "              INVENTORY\n";
  cout << "====================================\n";

  cout << "Meat       : " << meat << "\n";
  cout << "Fish       : " << fish << "\n";
  cout << "Medicine   : " << medicine << "\n";
  cout << "Water      : " << water << "\n";
  cout << "Toys       : " << toys << "\n";

  cout << "====================================\n";
}

// =====================================================
//                  MINI GAME FUNCTION
// =====================================================

void miniGame(int &coins, int &happiness) {
  int guess;

  int secret = rand() % 10 + 1;

  cout << "\n";
  cout << "====================================\n";
  cout << "              MINI GAME\n";
  cout << "====================================\n";

  cout << "Guess a number from 1 to 10: ";
  cin >> guess;

  if (guess == secret) {
    cout << "\nCorrect!\n";
    cout << "You won 50 coins!\n";

    coins += 50;
    happiness += 10;

    if (happiness > 100)
      happiness = 100;
  } else {
    cout << "\nWrong guess!\n";
    cout << "Correct number was: " << secret << "\n";

    happiness -= 5;

    if (happiness < 0)
      happiness = 0;
  }
}

// =====================================================
//                  STATUS FUNCTION
// =====================================================

void showStatus(int health, int energy, int hunger, int happiness, int coins,
                int day, string name) {
  cout << "\n";
  cout << "=============================================\n";
  cout << "              TIGER STATUS\n";
  cout << "=============================================\n";

  cout << "Tiger Name : " << name << "\n";
  cout << "Day        : " << day << "\n";
  cout << "Coins      : " << coins << "\n";

  cout << "\n";

  cout << "Health     : ";
  progressBar(health);
  cout << " " << health << "/100\n";

  cout << "Energy     : ";
  progressBar(energy);
  cout << " " << energy << "/100\n";

  cout << "Hunger     : ";
  progressBar(hunger);
  cout << " " << hunger << "/100\n";

  cout << "Happiness  : ";
  progressBar(happiness);
  cout << " " << happiness << "/100\n";

  cout << "=============================================\n";

  checkAchievements(health, energy, hunger, happiness, coins, day);
}

// =====================================================
//                  PROGRESS BAR
// =====================================================

void progressBar(int value) {
  cout << "[";

  int bars = value / 10;

  for (int i = 0; i < 10; i++) {
    if (i < bars) {
      cout << "#";
    } else {
      cout << "-";
    }
  }

  cout << "]";
}

// =====================================================
//                  UPDATE TIGER
// =====================================================

void updateTiger(int &health, int &hunger, int &happiness) {
  // Hunger increases slightly after actions
  hunger += 2;

  // Happiness decreases slightly
  happiness -= 2;

  if (hunger > 100)
    hunger = 100;

  if (happiness < 0)
    happiness = 0;

  // If tiger is extremely hungry
  if (hunger >= 90) {
    cout << "\nWARNING: Tiger is extremely hungry!\n";

    health -= 10;

    if (health < 0)
      health = 0;
  }

  // Happiness warning
  if (happiness <= 20) {
    cout << "\nWARNING: Tiger is very unhappy!\n";
  }

  // Health warning
  if (health > 0 && health < 30) {
    cout << "\nALERT: Tiger is sick!\n";
    cout << "Give medicine or feed the tiger.\n";
  }

  if (health > 100)
    health = 100;
}

// =====================================================
//                  RANDOM EVENT
// =====================================================

void randomEvent(int &health, int &energy, int &hunger, int &happiness,
                 int &coins) {
  int eventNumber = rand() % 5;

  cout << "\n";
  cout << "====================================\n";
  cout << "            RANDOM EVENT\n";
  cout << "====================================\n";

  if (eventNumber == 0) {
    cout << "Tiger found some food!\n";

    hunger -= 15;
    happiness += 5;

    if (hunger < 0)
      hunger = 0;

    if (happiness > 100)
      happiness = 100;
  }

  else if (eventNumber == 1) {
    cout << "Tiger found some coins!\n";

    coins += 20;

    cout << "You received 20 coins.\n";
  }

  else if (eventNumber == 2) {
    cout << "Tiger played in the garden.\n";

    happiness += 10;
    energy -= 10;

    if (happiness > 100)
      happiness = 100;

    if (energy < 0)
      energy = 0;
  }

  else if (eventNumber == 3) {
    cout << "Tiger became a little tired.\n";

    energy -= 15;

    if (energy < 0)
      energy = 0;
  }

  else {
    cout << "Nothing special happened today.\n";
  }

  cout << "====================================\n";
}

// =====================================================
//                  NEXT DAY FUNCTION
// =====================================================

void nextDay(int &day, int &health, int &energy, int &hunger, int &happiness,
             int &coins) {
  day++;

  cout << "\n";
  cout << "====================================\n";
  cout << "          NEW DAY: " << day << "\n";
  cout << "====================================\n";

  hunger += 10;
  energy += 10;
  happiness -= 5;

  if (hunger > 100)
    hunger = 100;

  if (energy > 100)
    energy = 100;

  if (happiness < 0)
    happiness = 0;

  randomEvent(health, energy, hunger, happiness, coins);

  if (hunger >= 90) {
    health -= 10;

    cout << "\nTiger lost health because of hunger.\n";
  }

  if (health < 0)
    health = 0;

  cout << "\nDay " << day << " has started.\n";
  cout << "Take care of your tiger!\n";
}

// =====================================================
//                ACHIEVEMENT FUNCTION
// =====================================================

void checkAchievements(int health, int energy, int hunger, int happiness,
                       int coins, int day) {
  cout << "\nAchievements:\n";

  if (health >= 90) {
    cout << "* Healthy Tiger\n";
  }

  if (happiness >= 90) {
    cout << "* Happy Tiger\n";
  }

  if (energy >= 90) {
    cout << "* Full Energy\n";
  }

  if (hunger <= 20) {
    cout << "* Well Fed\n";
  }

  if (coins >= 200) {
    cout << "* Rich Owner\n";
  }

  if (day >= 5) {
    cout << "* 5 Days Completed\n";
  }

  if (day >= 10) {
    cout << "* Tiger Master\n";
  }
}

// =====================================================
//                    TIGER DISPLAY
// =====================================================

void showTiger() {
  cout << "\n";
  cout << "====================================\n";
  cout << "             YOUR TIGER\n";
  cout << "====================================\n";

  cout << "             /\\_/\\\\\n";
  cout << "            ( o.o )\n";
  cout << "             > ^ <\n";
  cout << "          /---------\\\\\n";
  cout << "         /   TIGER    \\\\\n";
  cout << "        /______________\\\\\n";

  cout << "\n";
  cout << "             ROAR!\n";

  cout << "====================================\n";
}

// =====================================================
//                    PAUSE FUNCTION
// =====================================================

void pauseGame() {
  cout << "\nPress Enter to continue...";

  cin.ignore();
  cin.get();
}