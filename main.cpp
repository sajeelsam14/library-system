#include <iostream>
#include "sqlite3.h"

using namespace std;

template <class T>
class Linklist;

template <class T>
class Node
{
private:
    T data;
    Node *next;

public:
    Node()
    {
        this->next = nullptr;
    }
    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
    }
    friend class Linklist<T>;
};

template <class T>
class Linklist
{
private:
    Node<T> *head;

public:
    Linklist()
    {
        this->head = nullptr;
    }
    ~Linklist()
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            Node<T> *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    bool insertData(T data)
    {
        if (this->head != nullptr)
        {
            Node<T> *curr = new Node<T>(data);
            curr->next = this->head;
            this->head = curr;
            return true;
        }
        this->head = new Node<T>(data);
        return true;
    }
};

enum UserType
{
    STUDENT,
    TEACHER
};

string userTypeToString(UserType type)
{
    switch (type)
    {
    case STUDENT:
        return "student";
    case TEACHER:
        return "teacher";
    default:
        return "unknown";
    }
}

class User
{
protected:
    static int nextUserID;
    int userID;
    string name;
    UserType type;

public:
    User(string name, UserType type)
    {
        this->userID = ++nextUserID;
        this->name = name;
        this->type = type;
    }
    virtual void displayUserDetails() {}
};

int User::nextUserID = 0;

class Student : private User
{
private:
    int yearOfStudies;
    Linklist<int> borrowBookedID;

public:
    Student(string name, int yearOfStudies) : User(name, STUDENT)
    {
        this->yearOfStudies = yearOfStudies;
    }
    void displayUserDetails(void) override
    {
        cout << "Student ID: " << User::userID << endl;
        cout << "Student Name: " << this->name << endl;
        cout << "Student Year of Studies: " << this->yearOfStudies << endl;
    }
};

class Teacher : private User
{
private:
    string department;
    Linklist<int> borrowBookedID;

public:
    Teacher(string department, string name) : User(name, TEACHER)
    {
        this->department = department;
    }

    void displayUserDetails(void) override
    {
        cout << "Teacher ID: " << User::userID << endl;
        cout << "Teacher Department: " << this->name << endl;
        cout << "Teacher Name: " << this->name << endl;
    }
};

class Book
{
private:
    static int nextBookID;
    int bookID;
    string title;
    string author;
    bool isAvaible;

public:
    Book(string title, string author, bool isAvaible)
    {
        this->bookID = ++nextBookID;
        this->author = author;
        this->isAvaible = isAvaible;
        this->title = title;
    }

    void displayBookDetails(void) const
    {
        cout << "Book ID: " << this->bookID << endl;
        cout << "Book Title: " << this->title << endl;
        cout << "Book author: " << this->author << endl;
        cout << "IsAvaible? " << (this->isAvaible ? "Yes" : "No") << endl;
    }
};

int Book::nextBookID = 0;

class Library
{
private:
    Linklist<Book> books;
    Linklist<User *> users;
    Linklist<int> transactionHistory;

public:
    void addBook(Book &book) {};
    void addUser(User &user) {}
    Book *searchBook(int id) const { return nullptr; };
    User *searchUser(int id) const { return nullptr; };
    void borrowBook(int bookID, int userID) {};
    void returnBook(int bookID, int userID) {};
};

int main()
{
    sqlite3 *db;
    const char *dbPath = "D:/CPP/library-system/db/library-system.db";
    int exit = sqlite3_open(dbPath, &db);
    if (exit)
    {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return -1;
    }
    else
    {
        cout << "Opened database successfully!" << endl;
    }
    sqlite3_close(db);
    return 0;
}
