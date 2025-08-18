import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]  # Assuming password is the second column
        if stored_password == password:
            print("Login successful! Redirecting to home page.")
            return "home"
        else:
            print("Incorrect password.")
            return "password_error"
    else:
        print("Username not found.")
        return "username_not_found"

# Simulate user input and call login function
username = input("Enter your username: ")
password = input("Enter your password: ")
result = login(username, password)
if result == "home":
    print("Welcome to the home page!")