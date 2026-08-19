
// Zaeem ( SOLO )

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Maximum number of books and members
const int MAX_BOOKS = 100;
const int MAX_MEMBERS = 100;

// Structure for storing book information
struct Book {
  int bookId;
  string title;
  string author;
  string category;
  int quantity;
  int available;
};

// Structure for storing library member information
struct Member {
  int memberId;
  string name;
  string phone;
  string department;
};

// Structure for storing issued book information
struct Issue {
  int issueId;
  int bookId;
  int memberId;
  string issueDate;
  string returnDate;
  bool returned;
};

// Function prototypes
int loadBooks(Book books[]);
void saveBooks(Book books[], int count);
int loadMembers(Member members[]);
void saveMembers(Member members[], int count);
int loadIssues(Issue issues[]);
void saveIssues(Issue issues[], int count);

void addBook(Book books[], int &count);
void displayBook(Book books[], int count);
void searchBook(Book books[], int count);
void updateBook(Book books[], int count);
void deleteBook(Book books[], int &count);
void displayAllBooks(Book books[], int count);

void addMember(Member members[], int &count);
void displayMember(Member members[], int count);
void searchMember(Member members[], int count);
void updateMember(Member members[], int count);
void deleteMember(Member members[], int &count);
void displayAllMembers(Member members[], int count);

void issueBook(Book books[], int bookCount, Member members[], int memberCount,
               Issue issues[], int &issueCount);

void returnBook(Book books[], int bookCount, Issue issues[], int issueCount);

void displayIssues(Issue issues[], int issueCount);

int findBook(Book books[], int count, int id);
int findMember(Member members[], int count, int id);
int findIssue(Issue issues[], int count, int id);

void showBook(Book book);
void showMember(Member member);
void showIssue(Issue issue);

void clearInput();
void pauseScreen();

// Load books from file
int loadBooks(Book books[]) {
  ifstream file("books.txt");
  int count = 0;

  if (!file) {
    return 0;
  }

  while (count < MAX_BOOKS) {
    if (!(file >> books[count].bookId)) {
      break;
    }

    file.ignore(1000, '\n');

    getline(file, books[count].title, '|');
    getline(file, books[count].author, '|');
    getline(file, books[count].category, '|');

    file >> books[count].quantity;
    file >> books[count].available;
    file.ignore(1000, '\n');

    count++;
  }

  file.close();
  return count;
}

// Save books to file
void saveBooks(Book books[], int count) {
  ofstream file("books.txt");

  if (!file) {
    cout << "\nUnable to save books.\n";
    return;
  }

  for (int i = 0; i < count; i++) {
    file << books[i].bookId << endl;
    file << books[i].title << "|";
    file << books[i].author << "|";
    file << books[i].category << "|" << endl;
    file << books[i].quantity << endl;
    file << books[i].available << endl;
  }

  file.close();
}

// Load members from file
int loadMembers(Member members[]) {
  ifstream file("members.txt");
  int count = 0;

  if (!file) {
    return 0;
  }

  while (count < MAX_MEMBERS) {
    if (!(file >> members[count].memberId)) {
      break;
    }

    file.ignore(1000, '\n');

    getline(file, members[count].name, '|');
    getline(file, members[count].phone, '|');
    getline(file, members[count].department, '|');

    count++;
  }

  file.close();
  return count;
}

// Save members to file
void saveMembers(Member members[], int count) {
  ofstream file("members.txt");

  if (!file) {
    cout << "\nUnable to save members.\n";
    return;
  }

  for (int i = 0; i < count; i++) {
    file << members[i].memberId << endl;
    file << members[i].name << "|";
    file << members[i].phone << "|";
    file << members[i].department << "|" << endl;
  }

  file.close();
}

// Load issued books from file
int loadIssues(Issue issues[]) {
  ifstream file("issues.txt");
  int count = 0;

  if (!file) {
    return 0;
  }

  while (count < MAX_BOOKS) {
    if (!(file >> issues[count].issueId)) {
      break;
    }

    file >> issues[count].bookId;
    file >> issues[count].memberId;

    file.ignore(1000, '\n');

    getline(file, issues[count].issueDate, '|');
    getline(file, issues[count].returnDate, '|');

    file >> issues[count].returned;
    file.ignore(1000, '\n');

    count++;
  }

  file.close();
  return count;
}

// Save issued books
void saveIssues(Issue issues[], int count) {
  ofstream file("issues.txt");

  if (!file) {
    cout << "\nUnable to save issue records.\n";
    return;
  }

  for (int i = 0; i < count; i++) {
    file << issues[i].issueId << endl;
    file << issues[i].bookId << endl;
    file << issues[i].memberId << endl;
    file << issues[i].issueDate << "|";
    file << issues[i].returnDate << "|" << endl;
    file << issues[i].returned << endl;
  }

  file.close();
}

// Add a new book
void addBook(Book books[], int &count) {
  if (count >= MAX_BOOKS) {
    cout << "\nBook storage is full.\n";
    return;
  }

  Book book;

  cout << "\n========== ADD NEW BOOK ==========\n";

  cout << "Enter book ID: ";
  cin >> book.bookId;

  if (findBook(books, count, book.bookId) != -1) {
    cout << "Book ID already exists.\n";
    return;
  }

  clearInput();

  cout << "Enter book title: ";
  getline(cin, book.title);

  cout << "Enter author name: ";
  getline(cin, book.author);

  cout << "Enter category: ";
  getline(cin, book.category);

  cout << "Enter quantity: ";
  cin >> book.quantity;

  if (book.quantity <= 0) {
    cout << "Quantity must be greater than zero.\n";
    return;
  }

  book.available = book.quantity;

  books[count] = book;
  count++;

  saveBooks(books, count);

  cout << "\nBook added successfully.\n";
}

// Display one book
void displayBook(Book books[], int count) {
  int id;

  cout << "\nEnter book ID: ";
  cin >> id;

  int index = findBook(books, count, id);

  if (index == -1) {
    cout << "\nBook not found.\n";
    return;
  }

  showBook(books[index]);
}

// Search book by ID
void searchBook(Book books[], int count) {
  int id;

  cout << "\nEnter book ID to search: ";
  cin >> id;

  int index = findBook(books, count, id);

  if (index == -1) {
    cout << "\nNo book found.\n";
    return;
  }

  cout << "\n========== BOOK FOUND ==========\n";
  showBook(books[index]);
}

// Update book information
void updateBook(Book books[], int count) {
  int id;

  cout << "\nEnter book ID: ";
  cin >> id;

  int index = findBook(books, count, id);

  if (index == -1) {
    cout << "\nBook not found.\n";
    return;
  }

  clearInput();

  cout << "\nEnter new title: ";
  getline(cin, books[index].title);

  cout << "Enter new author: ";
  getline(cin, books[index].author);

  cout << "Enter new category: ";
  getline(cin, books[index].category);

  cout << "Enter new quantity: ";
  int newQuantity;
  cin >> newQuantity;

  if (newQuantity <= 0) {
    cout << "Invalid quantity.\n";
    return;
  }

  int issued = books[index].quantity - books[index].available;

  if (newQuantity < issued) {
    cout << "Quantity cannot be less than issued copies.\n";
    return;
  }

  books[index].quantity = newQuantity;
  books[index].available = newQuantity - issued;

  saveBooks(books, count);

  cout << "\nBook updated successfully.\n";
}

// Delete a book
void deleteBook(Book books[], int &count) {
  int id;

  cout << "\nEnter book ID to delete: ";
  cin >> id;

  int index = findBook(books, count, id);

  if (index == -1) {
    cout << "\nBook not found.\n";
    return;
  }

  if (books[index].available != books[index].quantity) {
    cout << "\nCannot delete a book with issued copies.\n";
    return;
  }

  for (int i = index; i < count - 1; i++) {
    books[i] = books[i + 1];
  }

  count--;

  saveBooks(books, count);

  cout << "\nBook deleted successfully.\n";
}

// Display all books
void displayAllBooks(Book books[], int count) {
  if (count == 0) {
    cout << "\nNo books available.\n";
    return;
  }

  cout << "\n================ ALL BOOKS ================\n";

  cout << left << setw(8) << "ID" << setw(25) << "Title" << setw(20) << "Author"
       << setw(15) << "Category" << setw(10) << "Qty" << setw(10) << "Avail"
       << endl;

  cout << "--------------------------------------------------------------------"
          "------\n";

  for (int i = 0; i < count; i++) {
    cout << left << setw(8) << books[i].bookId << setw(25) << books[i].title
         << setw(20) << books[i].author << setw(15) << books[i].category
         << setw(10) << books[i].quantity << setw(10) << books[i].available
         << endl;
  }
}

// Add a library member
void addMember(Member members[], int &count) {
  if (count >= MAX_MEMBERS) {
    cout << "\nMember storage is full.\n";
    return;
  }

  Member member;

  cout << "\n========== ADD MEMBER ==========\n";

  cout << "Enter member ID: ";
  cin >> member.memberId;

  if (findMember(members, count, member.memberId) != -1) {
    cout << "Member ID already exists.\n";
    return;
  }

  clearInput();

  cout << "Enter member name: ";
  getline(cin, member.name);

  cout << "Enter phone number: ";
  getline(cin, member.phone);

  cout << "Enter department/class: ";
  getline(cin, member.department);

  members[count] = member;
  count++;

  saveMembers(members, count);

  cout << "\nMember added successfully.\n";
}

// Display one member
void displayMember(Member members[], int count) {
  int id;

  cout << "\nEnter member ID: ";
  cin >> id;

  int index = findMember(members, count, id);

  if (index == -1) {
    cout << "\nMember not found.\n";
    return;
  }

  showMember(members[index]);
}

// Search member
void searchMember(Member members[], int count) {
  int id;

  cout << "\nEnter member ID to search: ";
  cin >> id;

  int index = findMember(members, count, id);

  if (index == -1) {
    cout << "\nNo member found.\n";
    return;
  }

  cout << "\n========== MEMBER FOUND ==========\n";
  showMember(members[index]);
}

// Update member
void updateMember(Member members[], int count) {
  int id;

  cout << "\nEnter member ID: ";
  cin >> id;

  int index = findMember(members, count, id);

  if (index == -1) {
    cout << "\nMember not found.\n";
    return;
  }

  clearInput();

  cout << "Enter new name: ";
  getline(cin, members[index].name);

  cout << "Enter new phone: ";
  getline(cin, members[index].phone);

  cout << "Enter new department/class: ";
  getline(cin, members[index].department);

  saveMembers(members, count);

  cout << "\nMember updated successfully.\n";
}

// Delete member
void deleteMember(Member members[], int &count) {
  int id;

  cout << "\nEnter member ID to delete: ";
  cin >> id;

  int index = findMember(members, count, id);

  if (index == -1) {
    cout << "\nMember not found.\n";
    return;
  }

  for (int i = index; i < count - 1; i++) {
    members[i] = members[i + 1];
  }

  count--;

  saveMembers(members, count);

  cout << "\nMember deleted successfully.\n";
}

// Display all members
void displayAllMembers(Member members[], int count) {
  if (count == 0) {
    cout << "\nNo members available.\n";
    return;
  }

  cout << "\n================ ALL MEMBERS ================\n";

  cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(18) << "Phone"
       << setw(20) << "Department" << endl;

  cout
      << "------------------------------------------------------------------\n";

  for (int i = 0; i < count; i++) {
    cout << left << setw(10) << members[i].memberId << setw(25)
         << members[i].name << setw(18) << members[i].phone << setw(20)
         << members[i].department << endl;
  }
}

// Issue a book to a member
void issueBook(Book books[], int bookCount, Member members[], int memberCount,
               Issue issues[], int &issueCount) {
  if (issueCount >= MAX_BOOKS) {
    cout << "\nIssue record storage is full.\n";
    return;
  }

  Issue issue;

  cout << "\n========== ISSUE BOOK ==========\n";

  cout << "Enter issue ID: ";
  cin >> issue.issueId;

  if (findIssue(issues, issueCount, issue.issueId) != -1) {
    cout << "Issue ID already exists.\n";
    return;
  }

  cout << "Enter book ID: ";
  cin >> issue.bookId;

  int bookIndex = findBook(books, bookCount, issue.bookId);

  if (bookIndex == -1) {
    cout << "Book not found.\n";
    return;
  }

  if (books[bookIndex].available <= 0) {
    cout << "No available copy of this book.\n";
    return;
  }

  cout << "Enter member ID: ";
  cin >> issue.memberId;

  int memberIndex = findMember(members, memberCount, issue.memberId);

  if (memberIndex == -1) {
    cout << "Member not found.\n";
    return;
  }

  clearInput();

  cout << "Enter issue date: ";
  getline(cin, issue.issueDate);

  issue.returnDate = "Not Returned";
  issue.returned = false;

  issues[issueCount] = issue;
  issueCount++;

  books[bookIndex].available--;

  saveIssues(issues, issueCount);
  saveBooks(books, bookCount);

  cout << "\nBook issued successfully.\n";
}

// Return a book
void returnBook(Book books[], int bookCount, Issue issues[], int issueCount) {
  int issueId;

  cout << "\n========== RETURN BOOK ==========\n";
  cout << "Enter issue ID: ";
  cin >> issueId;

  int issueIndex = findIssue(issues, issueCount, issueId);

  if (issueIndex == -1) {
    cout << "\nIssue record not found.\n";
    return;
  }

  if (issues[issueIndex].returned) {
    cout << "\nThis book has already been returned.\n";
    return;
  }

  int bookIndex = findBook(books, bookCount, issues[issueIndex].bookId);

  if (bookIndex != -1) {
    books[bookIndex].available++;
  }

  clearInput();

  cout << "Enter return date: ";
  getline(cin, issues[issueIndex].returnDate);

  issues[issueIndex].returned = true;

  saveIssues(issues, issueCount);
  saveBooks(books, bookCount);

  cout << "\nBook returned successfully.\n";
}

// Display all issue records
void displayIssues(Issue issues[], int issueCount) {
  if (issueCount == 0) {
    cout << "\nNo issue records available.\n";
    return;
  }

  cout << "\n================ ISSUE RECORDS ================\n";

  cout << left << setw(10) << "Issue ID" << setw(10) << "Book ID" << setw(12)
       << "Member ID" << setw(18) << "Issue Date" << setw(18) << "Return Date"
       << setw(10) << "Status" << endl;

  cout << "--------------------------------------------------------------------"
          "--------\n";

  for (int i = 0; i < issueCount; i++) {
    string status;

    if (issues[i].returned) {
      status = "Returned";
    } else {
      status = "Issued";
    }

    cout << left << setw(10) << issues[i].issueId << setw(10)
         << issues[i].bookId << setw(12) << issues[i].memberId << setw(18)
         << issues[i].issueDate << setw(18) << issues[i].returnDate << setw(10)
         << status << endl;
  }
}

// Find book index
int findBook(Book books[], int count, int id) {
  for (int i = 0; i < count; i++) {
    if (books[i].bookId == id) {
      return i;
    }
  }

  return -1;
}

// Find member index
int findMember(Member members[], int count, int id) {
  for (int i = 0; i < count; i++) {
    if (members[i].memberId == id) {
      return i;
    }
  }

  return -1;
}

// Find issue index
int findIssue(Issue issues[], int count, int id) {
  for (int i = 0; i < count; i++) {
    if (issues[i].issueId == id) {
      return i;
    }
  }

  return -1;
}

// Display book details
void showBook(Book book) {
  cout << "\n----------------------------------------\n";
  cout << "Book ID       : " << book.bookId << endl;
  cout << "Title         : " << book.title << endl;
  cout << "Author        : " << book.author << endl;
  cout << "Category      : " << book.category << endl;
  cout << "Quantity      : " << book.quantity << endl;
  cout << "Available     : " << book.available << endl;
  cout << "----------------------------------------\n";
}

// Display member details
void showMember(Member member) {
  cout << "\n----------------------------------------\n";
  cout << "Member ID     : " << member.memberId << endl;
  cout << "Name          : " << member.name << endl;
  cout << "Phone         : " << member.phone << endl;
  cout << "Department    : " << member.department << endl;
  cout << "----------------------------------------\n";
}

// Display issue details
void showIssue(Issue issue) {
  cout << "\n----------------------------------------\n";
  cout << "Issue ID      : " << issue.issueId << endl;
  cout << "Book ID       : " << issue.bookId << endl;
  cout << "Member ID     : " << issue.memberId << endl;
  cout << "Issue Date    : " << issue.issueDate << endl;
  cout << "Return Date   : " << issue.returnDate << endl;

  if (issue.returned) {
    cout << "Status        : Returned\n";
  } else {
    cout << "Status        : Issued\n";
  }

  cout << "----------------------------------------\n";
}

// Clear input buffer
void clearInput() { cin.ignore(1000, '\n'); }

// Pause screen
void pauseScreen() {
  cout << "\nPress Enter to continue...";
  cin.ignore(1000, '\n');
  cin.get();
}

// Main function
int main() {
  Book books[MAX_BOOKS];
  Member members[MAX_MEMBERS];
  Issue issues[MAX_BOOKS];

  int bookCount = loadBooks(books);
  int memberCount = loadMembers(members);
  int issueCount = loadIssues(issues);

  int choice;

  do {
    cout << "\n\n==============================================\n";
    cout << "          LIBRARY MANAGEMENT SYSTEM\n";
    cout << "==============================================\n";
    cout << "1. Add New Book\n";
    cout << "2. Display Book\n";
    cout << "3. Search Book\n";
    cout << "4. Update Book\n";
    cout << "5. Delete Book\n";
    cout << "6. Display All Books\n";
    cout << "----------------------------------------------\n";
    cout << "7. Add New Member\n";
    cout << "8. Display Member\n";
    cout << "9. Search Member\n";
    cout << "10. Update Member\n";
    cout << "11. Delete Member\n";
    cout << "12. Display All Members\n";
    cout << "----------------------------------------------\n";
    cout << "13. Issue Book\n";
    cout << "14. Return Book\n";
    cout << "15. Display Issue Records\n";
    cout << "16. Exit\n";
    cout << "==============================================\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail()) {
      cin.clear();
      clearInput();
      choice = 0;
    }

    switch (choice) {
    case 1:
      addBook(books, bookCount);
      pauseScreen();
      break;

    case 2:
      displayBook(books, bookCount);
      pauseScreen();
      break;

    case 3:
      searchBook(books, bookCount);
      pauseScreen();
      break;

    case 4:
      updateBook(books, bookCount);
      pauseScreen();
      break;

    case 5:
      deleteBook(books, bookCount);
      pauseScreen();
      break;

    case 6:
      displayAllBooks(books, bookCount);
      pauseScreen();
      break;

    case 7:
      addMember(members, memberCount);
      pauseScreen();
      break;

    case 8:
      displayMember(members, memberCount);
      pauseScreen();
      break;

    case 9:
      searchMember(members, memberCount);
      pauseScreen();
      break;

    case 10:
      updateMember(members, memberCount);
      pauseScreen();
      break;

    case 11:
      deleteMember(members, memberCount);
      pauseScreen();
      break;

    case 12:
      displayAllMembers(members, memberCount);
      pauseScreen();
      break;

    case 13:
      issueBook(books, bookCount, members, memberCount, issues, issueCount);
      pauseScreen();
      break;

    case 14:
      returnBook(books, bookCount, issues, issueCount);
      pauseScreen();
      break;

    case 15:
      displayIssues(issues, issueCount);
      pauseScreen();
      break;

    case 16:
      cout << "\nThank you for using Library Management System.\n";
      break;

    default:
      cout << "\nInvalid choice. Please try again.\n";
      pauseScreen();
    }

  } while (choice != 16);

  return 0;
}