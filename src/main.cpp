#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>

#include "../include/staff.h"
#include "../include/attendance.h"
#include "../include/payroll.h"

using namespace std;

int main()
{
    try
    {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();

        con = driver->connect(
            "tcp://127.0.0.1:3306",
            "root",
            "#123abcH5678"
        );

        con->setSchema("payroll_system");

        Staff staff(con);
        Attendance attendance(con);
        Payroll payroll(con);

        int choice;

        do
        {
cout << "\n============================";
cout << "\n SMART PAYROLL SYSTEM";
cout << "\n============================";

cout << "\n1. Add Staff";
cout << "\n2. View Staff";
cout << "\n3. Search Staff";
cout << "\n4. Update Staff";
cout << "\n5. Delete Staff";

cout << "\n6. Mark Attendance";
cout << "\n7. View Attendance";
cout << "\n8. Low Attendance Warning";

cout << "\n9. Generate Payroll";

cout << "\n10. Exit";

            cout << "\n\nEnter Choice: ";
            cin >> choice;

            switch(choice)
{
    case 1:
        staff.addStaff();
        break;

    case 2:
        staff.viewStaff();
        break;

    case 3:
        staff.searchStaff();
        break;

    case 4:
        staff.updateStaff();
        break;

    case 5:
        staff.deleteStaff();
        break;

    case 6:
        attendance.markAttendance();
        break;

    case 7:
        attendance.viewAttendance();
        break;

    case 8:
        attendance.lowAttendanceWarning();
        break;

    case 9:
        payroll.generatePayroll();
        break;

    case 10:
        cout << "\nExiting...\n";
        break;

    default:
        cout << "\nInvalid Choice!\n";
}

        } while(choice != 10);

        delete con;
    }
    catch(sql::SQLException &e)
    {
        cout << "ERROR: " << e.what() << endl;
    }

    return 0;
}