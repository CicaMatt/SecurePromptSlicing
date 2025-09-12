import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]  # assuming password is the second column
        if stored_password == password:
            print("Login successful")
            return redirect_to_home()
        else:
            print("Incorrect password")
    else:
        print("Username not found")

def redirect_to_home():
    print("Redirecting to home page...")