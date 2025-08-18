import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    if user:
        stored_password = user[1]
        if password == stored_password:
            redirect_to_home_page()
        else:
            return
    else:
        return

def redirect_to_home_page():
    print("Redirecting to home page...")

# Simulate login attempt
login('testuser', 'password123')