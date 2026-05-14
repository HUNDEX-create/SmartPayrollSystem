# 💼 Smart Staff Attendance & Payroll System

A C++ and MySQL-based payroll management system that automates staff management, attendance tracking, and salary calculation.

---

## 📌 Features

- Add, update, delete staff
- Mark attendance
- Generate payroll automatically
- Bonus & deduction system
- Search staff
- Low attendance warning
- Top performer detection
- MySQL database integration

---

## 🧰 Technologies Used

- C++
- MySQL
- MySQL Connector/C++
- Linux Mint

---

## 🚀 How to Run

### Compile
```bash
g++ src/main.cpp src/staff.cpp src/attendance.cpp src/payroll.cpp -o payroll_app -lmysqlcppconn
./payroll_app
CREATE DATABASE payroll_system;
nano README.md

