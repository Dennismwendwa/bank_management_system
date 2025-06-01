# 📘 Bank Management System (C++)

A secure, modular, and extensible **Bank Management System** developed in modern C++.
This system handles all essential banking operations from user authentication to
account management and transaction processing — built with clean architecture and
thread-safe file/database storage support.

---

## 🔧 Features

- ✅ User Registration & Login  
- ✅ Secure Password Handling  
- ✅ Duplicate Email/Username Prevention  
- ✅ Account Management (Create / Update / Delete)  
- ✅ Deposit & Withdrawal  
- ✅ Transaction History  
- ✅ Pluggable Storage System (CSV / PostgreSQL backend)  
- ✅ Thread-safe I/O using `std::mutex`  
- ❌ No GUI/frontend yet — console-based interaction only  

---

## 🛠️ Technologies Used

- **Language:** C++17  
- **Build System:** `Make`  
- **Password Hashing:** `bcrypt` 
- **Storage Interfaces:** File-based (CSV) + support for PostgreSQL via abstract interface  
- **Threading:** `std::mutex` for file locking  

---

## 📂 Project Structure

---

## ⚙️ How to Build and Run

### ✅ Prerequisites

- C++17-compatible compiler (e.g., `g++`)  
- `make` installed  
- PostgreSQL client libraries (optional, for DB backend)

### 🔨 Build the Project

```bash
make

./bin/bank_app

---
## 🧪 Sample Usage
Welcome to the Bank Management System!

1. Register
2. Log In
3. Exit

> 1

Enter your first name: Dennis  
Enter last name: Mwendwa  
Enter email: dennis@example.com  
Choose username: dennis_m  
Choose password: ********  

✅ Registration successful!

---

## 📌 Design Philosophy
- Clean Architecture: Storage-agnostic core logic with dependency injection
- Extensibility: Easily swap or extend storage backends via IStorage interface
- Testability: Clear separation of concerns for easier testing
- Security First: Planned use of password hashing & login status tracking

---

## 🧱 Storage Backends
📁 CSV Storage (Default)
- Thread-safe appending and retrieval from users.csv
- Uses std::mutex for concurrent access handling

## 🗃️ Database (PostgreSQL - Optional)
- PostgreSQL backend using the same abstract interface
- Planned for production-ready deployments
- Integration via libpqxx or similar driver

---

📈 Roadmap
Feature	Status
Console-based backend logic	✅ Complete
Abstract storage layer	✅ Complete
Email/username validation	✅ Complete
Full bcrypt password hashing	⏳ Planned
GUI or Web frontend	⏳ Planned
Full unit/integration testing	⏳ Planned

✍️ Contributing
Pull requests are welcome. To contribute:

Fork the repository

Create a new branch (git checkout -b feature/your-feature)

Commit your changes (git commit -m 'Add your feature')

Push to the branch (git push origin feature/your-feature)

Open a Pull Request

🧑‍💻 Author
Dennis Mwendwa
C++ Developer & Backend Engineer
LinkedIn | GitHub