import sqlite3

def create_connection():
    conn = sqlite3.connect('users.db')
    return conn

def login(username, password):
    conn = create_connection()
    cursor = conn.cursor()
    
    query = "SELECT * FROM users WHERE username = ?"
    cursor.execute(query, (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]
        if stored_password == password:
            redirect_to_home_page()
        else:
            return
    else:
        return

def redirect_to_home_page():
    print("Redirecting to home page...")

# Example usage
username = input("Enter username: ")
password = input("Enter password: ")
login(username, password)