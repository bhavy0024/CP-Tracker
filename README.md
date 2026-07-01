# 🚀 CP Tracker

A **Competitive Programming Tracker** built using **C++** and **SQLite3** to help competitive programmers efficiently organize and track solved problems. The application provides CRUD operations, searching, filtering, statistics, revision scheduling, logging, and CSV export through a clean console interface.

---

## ✨ Features

* ➕ Add new programming problems
* 📋 View all stored problems
* 🔍 Search problems by name
* 🏷️ Filter problems by platform
* ⭐ Filter problems by rating
* 📊 View statistics (total problems, average rating, difficulty distribution)
* 🔁 Maintain a revision list
* 📄 Export all records to CSV
* 📝 Log important operations
* 💾 Persistent storage using SQLite3

---

## 🛠️ Tech Stack

* **Language:** C++17
* **Database:** SQLite3
* **Programming Concepts:**

  * Object-Oriented Programming (OOP)
  * File Handling
  * Modular Programming
  * Prepared Statements
  * CRUD Operations

---

## 📂 Project Structure

```
CP-Tracker/
│
├── include/
│   ├── database.h
│   ├── problem.h
│   └── logger.h
│
├── src/
│   ├── main.cpp
│   ├── database.cpp
│   └── logger.cpp
│
├── .gitignore
└── README.md
```

---


## 📋 Requirements

* C++17 compatible compiler (GCC / MinGW / MSVC)
* SQLite3 library

---

## ⚙️ Installation

1. Clone the repository

```
git clone https://github.com/bhavy0024/CP-Tracker.git
```

2. Enter the project directory

```
cd CP-Tracker
```

3. Compile SQLite

```
gcc -c sqlite/sqlite3.c -o sqlite/sqlite3.o
```

4. Build the project

```
g++ -std=c++17 src/main.cpp src/database.cpp src/logger.cpp sqlite/sqlite3.o -Iinclude -o main.exe
```

5. Run

```
main.exe
```

---

## 📈 Future Improvements

* User authentication
* Difficulty-wise analytics
* Graphical User Interface (GUI)
* Cloud synchronization
* Automatic revision reminders

---

## 👨‍💻 Author

**Bhavy Hirpara**

---

