#include "../include/attendance.h"
#include <iostream>

using namespace std;

Attendance::Attendance(sql::Connection *connection)
{
    con = connection;
}

void Attendance::markAttendance()
{
    int staff_id;
    int days_present;
    string month;

    cout << "\nEnter Staff ID: ";
    cin >> staff_id;

    cout << "Enter Month: ";
    cin >> month;

    cout << "Enter Days Present: ";
    cin >> days_present;

    if(days_present < 0 || days_present > 30)
    {
        cout << "\nInvalid Attendance Days!\n";
        return;
    }

    sql::PreparedStatement *pstmt;

    pstmt = con->prepareStatement(
        "INSERT INTO attendance(staff_id, days_present, month) VALUES(?,?,?)"
    );

    pstmt->setInt(1, staff_id);
    pstmt->setInt(2, days_present);
    pstmt->setString(3, month);

    pstmt->execute();

    cout << "\nAttendance Recorded Successfully!\n";

    delete pstmt;
}

void Attendance::viewAttendance()
{
    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = con->createStatement();

    res = stmt->executeQuery(
        "SELECT * FROM attendance"
    );

    cout << "\n===== ATTENDANCE RECORDS =====\n";

    while(res->next())
    {
        cout << "\nAttendance ID: "
             << res->getInt("attendance_id");

        cout << "\nStaff ID: "
             << res->getInt("staff_id");

        cout << "\nMonth: "
             << res->getString("month");

        cout << "\nDays Present: "
             << res->getInt("days_present");

        cout << "\n-----------------------------\n";
    }

    delete res;
    delete stmt;
}

void Attendance::lowAttendanceWarning()
{
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    pstmt = con->prepareStatement(
        "SELECT * FROM attendance WHERE days_present < ?"
    );

    pstmt->setInt(1, 15);

    res = pstmt->executeQuery();

    cout << "\n===== LOW ATTENDANCE WARNING =====\n";

    bool found = false;

    while(res->next())
    {
        found = true;

        cout << "\nStaff ID: "
             << res->getInt("staff_id");

        cout << "\nMonth: "
             << res->getString("month");

        cout << "\nDays Present: "
             << res->getInt("days_present");

        cout << "\nWARNING: Low Attendance!\n";

        cout << "\n-----------------------------\n";
    }

    if(!found)
    {
        cout << "\nNo Low Attendance Records Found.\n";
    }

    delete res;
    delete pstmt;
}