#include "../include/payroll.h"
#include <iostream>

using namespace std;

Payroll::Payroll(sql::Connection *connection)
{
    con = connection;
}

void Payroll::generatePayroll()
{
    sql::Statement *stmt;
    sql::ResultSet *resStaff;

    stmt = con->createStatement();

    // Get all staff
    resStaff = stmt->executeQuery("SELECT * FROM staff");

    cout << "\n===== GENERATING PAYROLL =====\n";

    while(resStaff->next())
    {
        int staff_id = resStaff->getInt("staff_id");
        string name = resStaff->getString("name");
        double salary_per_day = resStaff->getDouble("salary_per_day");

        // Get attendance for this staff (latest month)
        sql::PreparedStatement *pstmt;
        sql::ResultSet *resAtt;

        pstmt = con->prepareStatement(
            "SELECT * FROM attendance WHERE staff_id=? ORDER BY attendance_id DESC LIMIT 1"
        );

        pstmt->setInt(1, staff_id);
        resAtt = pstmt->executeQuery();

        int days_present = 0;
        string month = "N/A";

        if(resAtt->next())
        {
            days_present = resAtt->getInt("days_present");
            month = resAtt->getString("month");
        }

        // BASIC SALARY
        double base_salary = salary_per_day * days_present;

        // BONUS & DEDUCTION RULES
        double bonus = 0;
        double deduction = 0;

        if(days_present >= 28)
            bonus = base_salary * 0.10;
        else if(days_present >= 25)
            bonus = base_salary * 0.05;
        else if(days_present < 20)
            deduction = base_salary * 0.10;

        double total_salary = base_salary + bonus - deduction;

        // Insert into payroll table
        sql::PreparedStatement *insertStmt;

        insertStmt = con->prepareStatement(
            "INSERT INTO payroll(staff_id, month, total_salary, bonus, deduction) VALUES(?,?,?,?,?)"
        );

        insertStmt->setInt(1, staff_id);
        insertStmt->setString(2, month);
        insertStmt->setDouble(3, total_salary);
        insertStmt->setDouble(4, bonus);
        insertStmt->setDouble(5, deduction);

        insertStmt->execute();

        // OUTPUT
        cout << "\nStaff: " << name;
        cout << "\nDays Present: " << days_present;
        cout << "\nBase Salary: " << base_salary;
        cout << "\nBonus: " << bonus;
        cout << "\nDeduction: " << deduction;
        cout << "\nTOTAL SALARY: " << total_salary;
        cout << "\n-------------------------\n";

        delete pstmt;
        delete resAtt;
        delete insertStmt;
    }

    delete resStaff;
    delete stmt;

    cout << "\nPAYROLL GENERATED SUCCESSFULLY!\n";
}