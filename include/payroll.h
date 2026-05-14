#ifndef PAYROLL_H
#define PAYROLL_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Payroll
{
private:
    sql::Connection *con;

public:
    Payroll(sql::Connection *connection);

    void generatePayroll();
};

#endif