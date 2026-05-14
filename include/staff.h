#ifndef STAFF_H
#define STAFF_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Staff
{
private:
    sql::Connection *con;

public:
    Staff(sql::Connection *connection);

    void addStaff();
    void viewStaff();
    void searchStaff();

    void updateStaff();
    void deleteStaff();
};

#endif