#include <iostream>
#include <string>
#include <optional>

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

    T &getData()
    {
        return data;
    }
    Node *getNext() const
    {
        return next;
    }
    void setNext(Node *nextNode)
    {
        next = nextNode;
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
            curr = curr->getNext();
            delete temp;
        }
    }

    Node<T> *getHead() const
    {
        return head;
    }

    bool insertData(const T &data)
    {
        Node<T> *newNode = new Node<T>(data);
        newNode->setNext(head);
        head = newNode;
        return true;
    }

    std::optional<T> searchData(int id)
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            if (curr->getData().getId() == id)
            {
                return curr->getData();
            }
            curr = curr->getNext();
        }
        return std::nullopt;
    }

    bool borrowBook(int id)
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            if (curr->getData().getId() == id)
            {
                curr->getData().setAvailability(false);
                return true;
            }
            curr = curr->getNext();
        }
        return false;
    }

    bool addBookInLinklist(int id)
    {
        Node<T> *curr = head;
        while (curr != nullptr)
        {
            if (curr->getData()->getId() == id)
            {
                if (curr->getData()->getBorrowedBooks().head == nullptr)
                {
                    curr->getData()->getBorrowedBooks().head = new Node<int>(id);
                    return true;
                }
                Node<int> *list = curr->getData()->getBorrowedBooks().head;
                while (list->getNext() != nullptr)
                {
                    list = list->getNext();
                }
                Node<int> *temp = new Node<int>(id);
                list->setNext(temp);
                return true;
            }
            curr = curr->getNext();
        }
        return false;
    }
};

enum class UserType
{
    STUDENT,
    TEACHER
};

string userTypeToString(UserType type)
{
    switch (type)
    {
    case UserType::STUDENT:
        return "student";
    case UserType::TEACHER:
        return "teacher";
    default:
        return "unknown";
    }
}

class User
{
protected:
    static int nextUserID;
    int id;
    string name;
    UserType type;
    Linklist<int> borrowBookedID;

public:
    User()
    {
        this->id = 0;
        this->name = "";
        this->type = UserType::STUDENT;
    }
    User(string name, UserType type)
    {
        this->id = ++nextUserID;
        this->name = name;
        this->type = type;
    }

    int getId() const
    {
        return id;
    }
    Linklist<int> &getBorrowedBooks()
    {
        return borrowBookedID;
    }

    virtual ~User() {}
    virtual void displayUserDetails() const = 0;
};

int User::nextUserID = 0;

class Student : public User
{
private:
    int yearOfStudies;

public:
    Student(string name, int yearOfStudies) : User(name, UserType::STUDENT)
    {
        this->yearOfStudies = yearOfStudies;
    }

    void displayUserDetails() const override
    {
        cout << "Student ID: " << id << endl;
        cout << "Student Name: " << name << endl;
        cout << "Year of Studies: " << yearOfStudies << endl;
    }
};

class Teacher : public User
{
private:
    string department;

public:
    Teacher(string name, string department) : User(name, UserType::TEACHER)
    {
        this->department = department;
    }

    void displayUserDetails() const override
    {
        cout << "Teacher ID: " << id << endl;
        cout << "Teacher Name: " << name << endl;
        cout << "Department: " << department << endl;
    }
};

class Book
{
private:
    static int nextBookID;
    int id;
    string title;
    string author;
    bool isAvaible;

public:
    Book()
    {
        this->id = 0;
        this->title = "";
        this->author = "";
        this->isAvaible = "";
    }

    Book(string title, string author, bool isAvaible)
    {
        this->id = ++nextBookID;
        this->title = title;
        this->author = author;
        this->isAvaible = isAvaible;
    }

    int getId() const
    {
        return id;
    }
    bool getAvailability() const
    {
        return isAvaible;
    }
    void setAvailability(bool availability)
    {
        isAvaible = availability;
    }

    void displayBookDetails() const
    {
        cout << "Book ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Available: " << (isAvaible ? "Yes" : "No") << endl;
    }
};

int Book::nextBookID = 0;
int main()
{
    Linklist<Book> bookList;
    Linklist<User *> userList;

    bookList.insertData(Book("C++ Programming", "Bjarne Stroustrup", true));
    bookList.insertData(Book("Data Structures and Algorithms", "Mark Allen Weiss", true));
    bookList.insertData(Book("Artificial Intelligence", "Stuart Russell", true));

    userList.insertData(new Student("Alice", 2));
    userList.insertData(new Teacher("Dr. Bob", "Computer Science"));

    int choice;

    do
    {
        cout << "\nLibrary Management System Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. List All Books\n";
        cout << "5. List All Users\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string title, author;
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            bookList.insertData(Book(title, author, true));
            cout << "Book added successfully!\n";
            break;
        }
        case 2:
        {
            int userId, bookId;
            cout << "Enter user ID: ";
            cin >> userId;
            cout << "Enter book ID: ";
            cin >> bookId;

            auto userOpt = userList.searchData(userId);
            auto bookOpt = bookList.searchData(bookId);

            if (userOpt && bookOpt && bookOpt->getAvailability())
            {
                User *user = *userOpt;
                Book &book = *bookOpt;

                book.setAvailability(false);
                user->getBorrowedBooks().insertData(bookId);
                cout << "Book borrowed successfully!\n";
            }
            else
            {
                cout << "Error: User or book not found, or book not available.\n";
            }
            break;
        }
        case 3:
        {
            int userId, bookId;
            cout << "Enter user ID: ";
            cin >> userId;
            cout << "Enter book ID: ";
            cin >> bookId;

            auto userOpt = userList.searchData(userId);
            auto bookOpt = bookList.searchData(bookId);

            if (userOpt && bookOpt)
            {
                User *user = *userOpt;
                Book &book = *bookOpt;

                book.setAvailability(true);
                cout << "Book returned successfully!\n";
            }
            else
            {
                cout << "Error: User or book not found.\n";
            }
            break;
        }
        case 4:
        {
            cout << "Listing all books:\n";
            Node<Book> *curr = bookList.getHead();
            while (curr)
            {
                curr->getData().displayBookDetails();
                curr = curr->getNext();
            }
            break;
        }
        case 5:
        {
            cout << "Listing all users:\n";
            Node<User *> *curr = userList.getHead();
            while (curr)
            {
                curr->getData()->displayUserDetails();
                curr = curr->getNext();
            }
            break;
        }
        case 6:
            cout << "Exiting program. Cleaning up memory...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 6);

    // Clean up dynamically allocated memory for users
    Node<User *> *curr = userList.getHead();
    while (curr)
    {
        delete curr->getData();
        curr = curr->getNext();
    }

    return 0;
}
