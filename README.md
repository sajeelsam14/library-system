# Library Management System

## Overview

The **Library Management System (LMS)** is designed to streamline the management of books, users, and transactions in a library environment. It is built using Object-Oriented Programming (OOP) principles and integrates basic Data Structures and Algorithms (DSA) for efficient operations. With SQLite3 for persistent data storage, the LMS enables easy book borrowing and returning for students and teachers.

## Features

- **User Management**: Register, search, update, and delete users.
- **Book Management**: Add, search, update, and delete books.
- **Transaction Tracking**: Monitor the status of borrowed and returned books with a history of transactions.

## System Architecture

### Classes and Relationships

#### User Class (Base Class)

- **Attributes**:
  - `int userID`
  - `std::string name`
  - `std::string type` (e.g., "Student" or "Teacher")
- **Functions**:
  - `virtual void displayUserDetails()`

#### Student Class (Inherits from User)

- **Attributes**:
  - `int yearOfStudy`
  - `std::vector<int> borrowedBookIDs`
- **Functions**:
  - `void displayUserDetails()`

#### Teacher Class (Inherits from User)

- **Attributes**:
  - `std::string department`
  - `std::vector<int> borrowedBookIDs`
- **Functions**:
  - `void displayUserDetails()`

#### Book Class

- **Attributes**:
  - `int bookID`
  - `std::string title`
  - `std::string author`
  - `bool isAvailable`
- **Functions**:
  - `void displayBookDetails()`

#### Library Class

- **Attributes**:
  - `std::vector<Book> books`
  - `std::vector<User*> users`
  - `std::stack<int> transactionHistory`
- **Functions**:
  - `void addBook(const Book&)`
  - `void addUser(User*)`
  - `Book* searchBook(int bookID)`
  - `User* searchUser(int userID)`
  - `void borrowBook(int bookID, int userID)`
  - `void returnBook(int bookID, int userID)`

## Database Integration (SQLite3)

### Tables

- **Users Table**:
  - Columns: `userID`, `name`, `type`, `yearOfStudy`, `department`, `borrowedBookIDs`
- **Books Table**:
  - Columns: `bookID`, `title`, `author`, `isAvailable`

### CRUD Operations

1. **Create**: Insert new records for books and users.
2. **Read**: Retrieve records using bookID or userID.
3. **Update**: Modify the availability status of books and user details.
4. **Delete**: Remove records of users or books when necessary.

## Data Structures and Algorithms

### Data Structures

1. **LinkedList**: Used for storing lists of `Book` and `User` objects, allowing fast iteration.
2. **Stack**: Tracks recent transactions for easy access to the last action.

### Algorithms

1. **Binary Search**: Utilized for efficient book retrieval in the `searchBook(int bookID)` function.
2. **Linear Search**: Applied in the `searchUser(int userID)` function for user lookup.

## Summary

The Library Management System combines OOP principles with effective data handling techniques, including:

- Inheritance, encapsulation, and polymorphism.
- Efficient search algorithms (Binary and Linear Search).
- Organized data structures (Vector and Stack).
- Persistent storage with SQLite3.

This project serves as a practical application of core programming concepts, enabling users to manage library resources effectively.

---

For more information or to contribute, feel free to reach out! Happy coding!
