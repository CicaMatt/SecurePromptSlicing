import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    if user:
        stored_password = user[1]
        if stored_password == password:
            print("Redirecting to home page...")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")
    conn.close()

# Example usage
username = input("Enter username: ")
password = input("Enter password: ")
login(username, password)