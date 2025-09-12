import sqlite3

def login(username, password):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]
        if stored_password == password:
            print("Redirecting to home page...")
            return "home"
        else:
            print("Incorrect password.")
            return
    else:
        print("Username not found.")
        return

# Simulate a login attempt
login('testuser', 'password123')