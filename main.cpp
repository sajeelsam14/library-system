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
    static int userID;
    string name;
    UserType type;

public:
    User(string name, UserType type)
    {
        ++userID;
        this->name = name;
        this->type = type;
    }
    virtual void displayUserDetails() {}
};

int User::userID = 0;

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
    void displayUserDetails() override
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

    void displayUserDetails() override
    {
        cout << "Teacher ID: " << User::userID << endl;
        cout << "Teacher Department: " << this->name << endl;
    }
};

int main()
{
    sqlite3 *db;
    const char *dbPath = "D:/CPP/library-system/db/example.db";
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
