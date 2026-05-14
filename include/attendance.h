#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Attendance
{
private:
    sql::Connection *con;

public:
    Attendance(sql::Connection *connection);

    void markAttendance();
    void viewAttendance();
    void lowAttendanceWarning();
};

#endif