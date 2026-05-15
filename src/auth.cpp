#include "../include/auth.h"
#include "../include/auth.h"
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

// Constructor
Auth::Auth(sql::Connection* conn) {
    this->con = conn;
}

// Login Function
bool Auth::login(string username, string password) {
    try {
        sql::PreparedStatement* pstmt;

        pstmt = con->prepareStatement(
            "SELECT * FROM users WHERE username=? AND password=?"
        );

        pstmt->setString(1, username);
        pstmt->setString(2, password);

        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            cout << "\nLOGIN SUCCESSFUL!\n";
            return true;
        } else {
            cout << "\nINVALID USERNAME OR PASSWORD\n";
            return false;
        }

    } catch (sql::SQLException &e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

// Create New User Function
void Auth::createUser() {

    try {
        string username, password, role;

        cout << "\n===== CREATE NEW USER =====\n";

        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;

        cout << "Enter Role (admin/hr): ";
        cin >> role;

        sql::PreparedStatement* pstmt;

        pstmt = con->prepareStatement(
            "INSERT INTO users(username, password, role) VALUES (?, ?, ?)"
        );

        pstmt->setString(1, username);
        pstmt->setString(2, password);
        pstmt->setString(3, role);

        pstmt->executeUpdate();

        cout << "\nUSER CREATED SUCCESSFULLY!\n";

    } catch (sql::SQLException &e) {
        cout << "Error: " << e.what() << endl;
    }
}
