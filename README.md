# 📘 Bank Management System (C++)

A secure, modular, and extensible **Bank Management System** developed in modern C++. This system handles all essential banking operations from user authentication to account management and transaction processing — built with clean architecture and thread-safe file/database storage support.

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