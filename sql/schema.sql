CREATE DATABASE IF NOT EXISTS payroll_system;

USE payroll_system;

CREATE TABLE staff (
    staff_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    salary_per_day DOUBLE NOT NULL
);

CREATE TABLE attendance (
    id INT PRIMARY KEY AUTO_INCREMENT,
    staff_id INT,
    month VARCHAR(20),
    days_present INT,
    FOREIGN KEY (staff_id) REFERENCES staff(staff_id)
);

CREATE TABLE payroll (
    payroll_id INT PRIMARY KEY AUTO_INCREMENT,
    staff_id INT,
    month VARCHAR(20),
    bonus DOUBLE,
    deduction DOUBLE,
    total_salary DOUBLE,
    FOREIGN KEY (staff_id) REFERENCES staff(staff_id)
);

