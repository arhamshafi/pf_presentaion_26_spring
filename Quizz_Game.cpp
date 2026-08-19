/*

 Usama ( SOLO )

    ====================================================================
    Project Name : Console-Based Quiz Game System
    Course       : Programming Fundamentals (PF)
    Language     : C++
    Description  : Interactive quiz game with categories, score saving,
                   lifelines, high score viewer, and admin system.
    ====================================================================
*/

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// =====================================================================
// DATA STRUCTURES
// =====================================================================

// Structure to hold individual question data
struct Question {
  string questionText;
  string options[4];
  int correctOption; // Index 1 to 4
  string category;   // e.g. CS, GK, Science
  int difficulty;    // 1 = Easy, 2 = Medium, 3 = Hard
};

// Structure to store player records
struct Player {
  string name;
  int score;
  string categoryChosen;
};

// =====================================================================
// FUNCTION DECLARATIONS (PROTOTYPES)
// =====================================================================

void showHeader();
void showMainMenu();
void startQuiz(Player &player, vector<Question> &questions);
void displayQuestion(const Question &q, int qNum, bool fiftyFiftyUsed);
void showHighScores();
void saveScore(const Player &p);
void loadDefaultQuestions(vector<Question> &questions);
void adminMenu(vector<Question> &questions);
void addNewQuestion(vector<Question> &questions);
void viewAllQuestions(const vector<Question> &questions);
void clearScreen();
void pauseConsole();

// =====================================================================
// MAIN FUNCTION
// =====================================================================

int main() {
  srand(time(0)); // Seed for random number generator

  vector<Question> questionBank;
  loadDefaultQuestions(questionBank);

  int choice = 0;
  Player currentPlayer;

  while (true) {
    clearScreen();
    showHeader();
    showMainMenu();

    cout << "Enter your choice (1-4): ";
    cin >> choice;

    // Input Validation
    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid input! Please enter a number." << endl;
      pauseConsole();
      continue;
    }

    switch (choice) {
    case 1: {
      clearScreen();
      showHeader();
      cin.ignore();
      cout << "Enter Player Name: ";
      getline(cin, currentPlayer.name);
      if (currentPlayer.name.empty()) {
        currentPlayer.name = "Anonymous";
      }
      startQuiz(currentPlayer, questionBank);
      saveScore(currentPlayer);
      pauseConsole();
      break;
    }
    case 2: {
      clearScreen();
      showHeader();
      showHighScores();
      pauseConsole();
      break;
    }
    case 3: {
      adminMenu(questionBank);
      break;
    }
    case 4: {
      cout << "\nThank you for playing the Quiz Game! Goodbye!" << endl;
      return 0;
    }
    default: {
      cout << "Invalid choice! Please choose between 1 and 4." << endl;
      pauseConsole();
      break;
    }
    }
  }

  return 0;
}

// =====================================================================
// DISPLAY & UTILITY FUNCTIONS
// =====================================================================

void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void pauseConsole() {
  cout << "\nPress Enter to continue...";
  cin.ignore();
  cin.get();
}

void showHeader() {
  cout << "=========================================================" << endl;
  cout << "              WELCOME TO THE QUIZ GAME SYSTEM            " << endl;
  cout << "=========================================================" << endl;
}

void showMainMenu() {
  cout << "1. Start Quiz Game" << endl;
  cout << "2. View High Scores" << endl;
  cout << "3. Admin Panel (Add/View Questions)" << endl;
  cout << "4. Exit Game" << endl;
  cout << "=========================================================" << endl;
}

// =====================================================================
// DEFAULT DATA LOADERS
// =====================================================================

void loadDefaultQuestions(vector<Question> &questions) {
  Question q;

  // Computer Science Questions
  q.questionText = "Which component is known as the brain of the computer?";
  q.options[0] = "1. RAM";
  q.options[1] = "2. CPU";
  q.options[2] = "3. Hard Disk";
  q.options[3] = "4. Motherboard";
  q.correctOption = 2;
  q.category = "CS";
  q.difficulty = 1;
  questions.push_back(q);

  q.questionText = "Which of the following is NOT a C++ keyword?";
  q.options[0] = "1. class";
  q.options[1] = "2. struct";
  q.options[2] = "3. function";
  q.options[3] = "4. virtual";
  q.correctOption = 3;
  q.category = "CS";
  q.difficulty = 2;
  questions.push_back(q);

  q.questionText = "What is the size of 'char' data type in standard C++?";
  q.options[0] = "1. 1 Byte";
  q.options[1] = "2. 2 Bytes";
  q.options[2] = "3. 4 Bytes";
  q.options[3] = "4. 8 Bytes";
  q.correctOption = 1;
  q.category = "CS";
  q.difficulty = 1;
  questions.push_back(q);

  q.questionText =
      "Which operator is used for dynamic memory allocation in C++?";
  q.options[0] = "1. malloc";
  q.options[1] = "2. new";
  q.options[2] = "3. alloc";
  q.options[3] = "4. create";
  q.correctOption = 2;
  q.category = "CS";
  q.difficulty = 2;
  questions.push_back(q);

  // General Knowledge Questions
  q.questionText = "What is the capital city of Pakistan?";
  q.options[0] = "1. Lahore";
  q.options[1] = "2. Karachi";
  q.options[2] = "3. Islamabad";
  q.options[3] = "4. Peshawar";
  q.correctOption = 3;
  q.category = "GK";
  q.difficulty = 1;
  questions.push_back(q);

  q.questionText = "Which planet is known as the Red Planet?";
  q.options[0] = "1. Earth";
  q.options[1] = "2. Mars";
  q.options[2] = "3. Jupiter";
  q.options[3] = "4. Venus";
  q.correctOption = 2;
  q.category = "GK";
  q.difficulty = 1;
  questions.push_back(q);

  q.questionText = "How many continents are there on Earth?";
  q.options[0] = "1. 5";
  q.options[1] = "2. 6";
  q.options[2] = "3. 7";
  q.options[3] = "4. 8";
  q.correctOption = 3;
  q.category = "GK";
  q.difficulty = 1;
  questions.push_back(q);

  q.questionText = "Which is the longest river in the world?";
  q.options[0] = "1. Amazon";
  q.options[1] = "2. Nile";
  q.options[2] = "3. Yangtze";
  q.options[3] = "4. Mississippi";
  q.correctOption = 2;
  q.category = "GK";
  q.difficulty = 2;
  questions.push_back(q);

  // Science Questions
  q.questionText = "What chemical element has the symbol 'O'?";
  q.options[0] = "1. Gold";
  q.options[1] = "2. Oxygen";
  q.options[2] = "3. Osmium";
  q.options[3] = "4. Hydrogen";
  q.correctOption = 2;
  q.category = "Science";
  q.difficulty = 1;
  questions.push_back(q);

  q.questionText = "What gas do plants absorb during photosynthesis?";
  q.options[0] = "1. Oxygen";
  q.options[1] = "2. Nitrogen";
  q.options[2] = "3. Carbon Dioxide";
  q.options[3] = "4. Hydrogen";
  q.correctOption = 3;
  q.category = "Science";
  q.difficulty = 1;
  questions.push_back(q);
}

// =====================================================================
// QUIZ GAMEPLAY LOGIC
// =====================================================================

void startQuiz(Player &player, vector<Question> &questions) {
  int catChoice = 0;
  string selectedCat = "";

  cout << "\nChoose Category:" << endl;
  cout << "1. Computer Science (CS)" << endl;
  cout << "2. General Knowledge (GK)" << endl;
  cout << "3. Science" << endl;
  cout << "4. All Categories Combined" << endl;
  cout << "Enter choice: ";
  cin >> catChoice;

  switch (catChoice) {
  case 1:
    selectedCat = "CS";
    break;
  case 2:
    selectedCat = "GK";
    break;
  case 3:
    selectedCat = "Science";
    break;
  default:
    selectedCat = "ALL";
    break;
  }

  player.categoryChosen = selectedCat;
  player.score = 0;

  // Filter eligible questions
  vector<Question> quizList;
  for (size_t i = 0; i < questions.size(); i++) {
    if (selectedCat == "ALL" || questions[i].category == selectedCat) {
      quizList.push_back(questions[i]);
    }
  }

  if (quizList.empty()) {
    cout << "\nNo questions available for this category!" << endl;
    return;
  }

  bool lifeline5050Available = true;
  int totalQuestionsToAsk = quizList.size() > 5 ? 5 : quizList.size();

  cout << "\nStarting Quiz for " << player.name << "!" << endl;
  cout << "Rules: 10 Points for correct answer, -5 for wrong answer." << endl;
  cout << "You have ONE 50-50 Lifeline. Type '50' to use it." << endl;
  cout << "=========================================================" << endl;

  for (int i = 0; i < totalQuestionsToAsk; i++) {
    // Pick a random question from list
    int randIdx = rand() % quizList.size();
    Question q = quizList[randIdx];

    // Remove asked question to prevent duplicate
    quizList.erase(quizList.begin() + randIdx);

    bool used5050InThisTurn = false;
    int userAns = 0;

    while (true) {
      cout << "\n---------------------------------------------------------"
           << endl;
      cout << "Question " << (i + 1) << " of " << totalQuestionsToAsk << endl;
      displayQuestion(q, i + 1, used5050InThisTurn);

      if (lifeline5050Available && !used5050InThisTurn) {
        cout << "[Tip: Enter '50' to use 50-50 Lifeline]" << endl;
      }

      cout << "Your Choice (1-4): ";
      cin >> userAns;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Try again." << endl;
        continue;
      }

      if (userAns == 50) {
        if (lifeline5050Available) {
          lifeline5050Available = false;
          used5050InThisTurn = true;
          cout << "\n>> 50-50 Lifeline Activated! Two wrong options hidden."
               << endl;
        } else {
          cout << "\n>> Lifeline already used!" << endl;
        }
        continue;
      }

      if (userAns >= 1 && userAns <= 4) {
        break;
      } else {
        cout << "Please select a valid option between 1 and 4." << endl;
      }
    }

    if (userAns == q.correctOption) {
      cout << "\n[CORRECT ANSWER!] You earned 10 points." << endl;
      player.score += 10;
    } else {
      cout << "\n[WRONG ANSWER!] Correct choice was: " << q.correctOption
           << endl;
      player.score -= 5;
      if (player.score < 0)
        player.score = 0;
    }
  }

  cout << "\n=========================================================" << endl;
  cout << "                     QUIZ COMPLETED                      " << endl;
  cout << "=========================================================" << endl;
  cout << "Player Name  : " << player.name << endl;
  cout << "Category     : " << player.categoryChosen << endl;
  cout << "Final Score  : " << player.score << " Points" << endl;
  cout << "=========================================================" << endl;
}

void displayQuestion(const Question &q, int qNum, bool fiftyFiftyUsed) {
  cout << "Category: [" << q.category << "]" << endl;
  cout << q.questionText << endl;

  if (!fiftyFiftyUsed) {
    for (int i = 0; i < 4; i++) {
      cout << "  " << q.options[i] << endl;
    }
  } else {
    // Show correct option + 1 wrong option
    int wrongShown = 0;
    for (int i = 0; i < 4; i++) {
      int optNum = i + 1;
      if (optNum == q.correctOption) {
        cout << "  " << q.options[i] << endl;
      } else if (wrongShown == 0) {
        cout << "  " << q.options[i] << endl;
        wrongShown++;
      } else {
        cout << "  " << optNum << ". [Hidden]" << endl;
      }
    }
  }
}

// =====================================================================
// FILE HANDLING FUNCTIONS
// =====================================================================

void saveScore(const Player &p) {
  ofstream outFile("highscores.txt", ios::app);
  if (!outFile) {
    cout << "Error opening highscores.txt file for writing!" << endl;
    return;
  }

  outFile << p.name << " " << p.categoryChosen << " " << p.score << endl;
  outFile.close();
  cout << "Score successfully saved to highscores.txt!" << endl;
}

void showHighScores() {
  ifstream inFile("highscores.txt");
  if (!inFile) {
    cout << "No High Score records found yet!" << endl;
    return;
  }

  cout << "=========================================================" << endl;
  cout << "                   HIGH SCORES BOARD                     " << endl;
  cout << "=========================================================" << endl;
  cout << left << setw(20) << "Player Name" << setw(15) << "Category"
       << setw(10) << "Score" << endl;
  cout << "---------------------------------------------------------" << endl;

  string name, category;
  int score;
  int count = 0;

  while (inFile >> name >> category >> score) {
    cout << left << setw(20) << name << setw(15) << category << setw(10)
         << score << endl;
    count++;
  }

  if (count == 0) {
    cout << "No score records available." << endl;
  }

  inFile.close();
  cout << "=========================================================" << endl;
}

// =====================================================================
// ADMIN FUNCTIONS
// =====================================================================

void adminMenu(vector<Question> &questions) {
  int adminChoice = 0;
  string password = "";

  clearScreen();
  showHeader();
  cout << "Enter Admin Password: ";
  cin >> password;

  if (password != "admin123") {
    cout << "Incorrect Password! Access Denied." << endl;
    pauseConsole();
    return;
  }

  while (true) {
    clearScreen();
    showHeader();
    cout << "                   ADMIN CONTROL PANEL                   " << endl;
    cout << "=========================================================" << endl;
    cout << "1. Add New Question" << endl;
    cout << "2. View All Questions" << endl;
    cout << "3. Total Questions Count" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "=========================================================" << endl;
    cout << "Enter choice: ";
    cin >> adminChoice;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid input!" << endl;
      pauseConsole();
      continue;
    }

    switch (adminChoice) {
    case 1:
      addNewQuestion(questions);
      pauseConsole();
      break;
    case 2:
      viewAllQuestions(questions);
      pauseConsole();
      break;
    case 3:
      cout << "\nTotal questions currently loaded: " << questions.size()
           << endl;
      pauseConsole();
      break;
    case 4:
      return;
    default:
      cout << "Invalid Option!" << endl;
      pauseConsole();
      break;
    }
  }
}

void addNewQuestion(vector<Question> &questions) {
  Question q;
  cin.ignore();

  cout << "\nEnter Question Text: ";
  getline(cin, q.questionText);

  for (int i = 0; i < 4; i++) {
    cout << "Enter Option " << (i + 1) << ": ";
    string opt;
    getline(cin, opt);

    char optNum = '1' + i;
    q.options[i] = string(1, optNum) + ". " + opt;
  }

  cout << "Enter Correct Option Number (1-4): ";
  cin >> q.correctOption;

  cout << "Enter Category (e.g., CS, GK, Science): ";
  cin >> q.category;

  q.difficulty = 1; // Default difficulty

  questions.push_back(q);
  cout << "\nQuestion added successfully to current session!" << endl;
}

void viewAllQuestions(const vector<Question> &questions) {
  cout << "\n=========================================================" << endl;
  cout << "                    ALL LOADED QUESTIONS                 " << endl;
  cout << "=========================================================" << endl;

  for (size_t i = 0; i < questions.size(); i++) {
    cout << "Q" << (i + 1) << " [" << questions[i].category
         << "]: " << questions[i].questionText << endl;
    for (int j = 0; j < 4; j++) {
      cout << "   " << questions[i].options[j] << endl;
    }
    cout << "   Correct Answer: Option " << questions[i].correctOption << endl;
    cout << "---------------------------------------------------------" << endl;
  }
}