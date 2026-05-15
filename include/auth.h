#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>

using namespace std;

class Auth {
private:
    sql::Connection* con;

public:
    // Constructor
    Auth(sql::Connection* conn);

    // Login function
    bool login(string username, string password);

    // Create new user
    void createUser();
};

#endif
