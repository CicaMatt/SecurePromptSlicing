import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]
        if stored_password == password:
            return redirect_to_home_page()
        else:
            return "Incorrect password"
    else:
        return "Username not found"

def redirect_to_home_page():
    print("Redirecting to home page...")
    # Code for redirection goes here

# Example usage
username = input("Enter username: ")
password = input("Enter password: ")
login(username, password)