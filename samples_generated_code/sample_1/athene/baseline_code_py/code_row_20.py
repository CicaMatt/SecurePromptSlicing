import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]  # Assuming password is the second column in the table
        if stored_password == password:
            print("Redirecting to home page...")
            return "home"
        else:
            print("Incorrect password.")
            return
    else:
        print("Username not found.")
        return

# Example usage (simulating user input)
username = input("Enter username: ")
password = input("Enter password: ")
login(username, password)