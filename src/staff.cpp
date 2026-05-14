#include "../include/staff.h"
#include <iostream>
#include <limits>

using namespace std;

Staff::Staff(sql::Connection *connection)
{
    con = connection;
}

void Staff::addStaff()
{
    string name, department;
    float salary;

    cout << "\nEnter Staff Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter Department: ";
    getline(cin, department);

    cout << "Enter Salary Per Day: ";
    cin >> salary;

    sql::PreparedStatement *pstmt;

    pstmt = con->prepareStatement(
        "INSERT INTO staff(name, salary_per_day, department) VALUES(?,?,?)"
    );

    pstmt->setString(1, name);
    pstmt->setDouble(2, salary);
    pstmt->setString(3, department);

    pstmt->execute();

    cout << "\nStaff Added Successfully!\n";

    delete pstmt;
}

void Staff::viewStaff()
{
    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = con->createStatement();

    res = stmt->executeQuery("SELECT * FROM staff");

    cout << "\n===== STAFF LIST =====\n";

    while(res->next())
    {
        cout << "\nID: "
             << res->getInt("staff_id");

        cout << "\nName: "
             << res->getString("name");

        cout << "\nDepartment: "
             << res->getString("department");

        cout << "\nSalary/Day: "
             << res->getDouble("salary_per_day");

        cout << "\n----------------------\n";
    }

    delete res;
    delete stmt;
}

void Staff::searchStaff()
{
    int id;

    cout << "\nEnter Staff ID: ";
    cin >> id;

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    pstmt = con->prepareStatement(
        "SELECT * FROM staff WHERE staff_id=?"
    );

    pstmt->setInt(1, id);

    res = pstmt->executeQuery();

    if(res->next())
    {
        cout << "\nStaff Found!\n";

        cout << "ID: "
             << res->getInt("staff_id");

        cout << "\nName: "
             << res->getString("name");

        cout << "\nDepartment: "
             << res->getString("department");

        cout << "\nSalary/Day: "
             << res->getDouble("salary_per_day");

        cout << endl;
    }
    else
    {
        cout << "\nStaff Not Found!\n";
    }

    delete res;
    delete pstmt;
}

void Staff::updateStaff()
{
    int id;
    string name, department;
    float salary;

    cout << "\nEnter Staff ID to Update: ";
    cin >> id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter New Name: ";
    getline(cin, name);

    cout << "Enter New Department: ";
    getline(cin, department);

    cout << "Enter New Salary Per Day: ";
    cin >> salary;

    sql::PreparedStatement *pstmt;

    pstmt = con->prepareStatement(
        "UPDATE staff SET name=?, department=?, salary_per_day=? WHERE staff_id=?"
    );

    pstmt->setString(1, name);
    pstmt->setString(2, department);
    pstmt->setDouble(3, salary);
    pstmt->setInt(4, id);

    int rows = pstmt->executeUpdate();

    if(rows > 0)
        cout << "\nStaff Updated Successfully!\n";
    else
        cout << "\nStaff ID Not Found!\n";

    delete pstmt;
}

void Staff::deleteStaff()
{
    int id;

    cout << "\nEnter Staff ID to Delete: ";
    cin >> id;

    sql::PreparedStatement *pstmt;

    pstmt = con->prepareStatement(
        "DELETE FROM staff WHERE staff_id=?"
    );

    pstmt->setInt(1, id);

    int rows = pstmt->executeUpdate();

    if(rows > 0)
        cout << "\nStaff Deleted Successfully!\n";
    else
        cout << "\nStaff ID Not Found!\n";

    delete pstmt;
}