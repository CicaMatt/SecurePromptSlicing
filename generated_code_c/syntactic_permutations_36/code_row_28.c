++
    #include <iostream>

    using namespace std;

    string login(string username, string password) {
        if (username == "admin" && password == "12345") {
            return "home";
        } else {
            return "";
        }
    }

    int main() {
        string username;
        cout << "Enter username: ";
        cin >> username;

        string password;
        cout << "Enter password: ";
        cin >> password;

        string home = login(username, password);
        if (home != "") {
            cout << "Login successful. Redirecting to home page." << endl;
        } else {
            cout << "Invalid credentials." << endl;
        }
    }