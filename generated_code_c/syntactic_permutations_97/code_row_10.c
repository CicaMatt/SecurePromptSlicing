// This code requires C++, <string>, <cryptopp>, <mysql>
// compile with g++ -std=c++17 -lcryptopp -lmysqlclient

#include <iostream>
#include <string>

using namespace std;

#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/sha.h"
#include "mysql/mysql.h"

int main()
{
    MYSQL mysql;
    string username, password, first_name, last_name, email;

    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    cout << "Enter first name: ";
    getline(cin, first_name);
    cout << "Enter last name: ";
    getline(cin, last_name);
    cout << "Enter email address: ";
    getline(cin, email);

    char *hashed_password = new char[41]; // 40-char hexadecimal hash string + terminating null character

    CryptoPP::SHA256 sha256;
    CryptoPP::StringSource ss(password, true, new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashed_password))));

    MYSQL_RES *result = mysql_store_result(&mysql);
    if (MYSQL_NUM_FIELDS(result) == 1)
    {
        cout << "Username already exists!" << endl;
    }
    else
    {
        string query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (" + username + ", " + hashed_password + ", " + first_name + ", " + last_name + ", " + email + ")";
        mysql_query(&mysql, query.c_str());
        cout << "Registration succeeded!" << endl;
    }

    delete[] hashed_password;

    return 0;
}