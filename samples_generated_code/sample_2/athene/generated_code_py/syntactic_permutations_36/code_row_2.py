import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    if user:
        stored_password = user[1]
        if stored_password == password:
            print("Login successful! Redirecting to home page...")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")
    conn.close()

# Simulate a login attempt
login('testuser', 'testpassword')