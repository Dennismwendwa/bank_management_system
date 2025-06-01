📘 Bank Management System (C++)

A secure, modular, and extensible Bank Management System developed in modern C++.
This system handles all essential banking operations from user authentication to 
account management and transaction processing:- built with clean architecture 
and thread-safe file/database storage support.

🔧 Features
✅ User Registration & Login

✅ Secure Password Handling

✅ Duplicate Email/Username Prevention

✅ Account Management (Create/Update/Delete)

✅ Deposit & Withdrawal

✅ Transaction History

✅ Pluggable Storage System (CSV / PostgreSQL backend)

✅ Thread-safe I/O using Mutexes

❌ No GUI/frontend yet — console-based interaction

🛠️ Technologies Used
Language: C++17

Build System: Make

Password Hashing: bcrypt (planned integration or stubbed)

Storage Interfaces: File-based (CSV) + support for PostgreSQL via abstract interface

Threading: std::mutex for file locking

📂 Project Structure
.
├── include/            # Header files (Auth, User, IStorage, etc.)
├── src/                # Source files
│   ├── accounts/       # Auth & User logic
│   ├── storage/        # CSV or DB storage backends
│   └── main.cpp        # Entry point
├── build/              # Compiled object files
├── Makefile            # Build instructions
└── README.md           # This file


⚙️ How to Build and Run
Prerequisites
C++17-compatible compiler (e.g., g++)

make installed

PostgreSQL client (optional, for DB backend)

Build the Project
make

Run the App
./bin/bank_app


🧪 Sample Usage
Welcome to the Bank Management System!
1. Register
2. Log In
3. Exit

> 1
Enter your first name: Dennis
Enter last name: mwendwa
Enter email: dennis@example.com
Choose username: dennis_m
Choose password: ********
✅ Registration successful!

📌 Design Philosophy
Clean Architecture: Storage-agnostic core logic with dependency injection

Extensibility: Easily swap or extend storage backends via IStorage interface

Testability: Clear separation of concerns for easier testing

Security First: Planned use of password hashing & login status tracking

🧱 Storage Backends
CSV Storage: Thread-safe appending and retrieval from users.csv

Database (Optional): PostgreSQL backend using the same interface structure


📈 Roadmap
 Console-based backend logic

 Abstract storage layer

 Email/username validation

 Full bcrypt password hashing

 GUI or Web frontend

 Full unit and integration tests


 🧑‍💻 Author
Dennis Mwendwa
C++ Developer & Backend Engineer
LinkedIn | GitHub (www.linkedin.com/in/dennis-musembi-83a18bb7)

📄 License
This project is licensed under the MIT License — see the LICENSE file for details.