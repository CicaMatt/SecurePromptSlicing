import sqlite3
from hashlib import sha256

def create_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users 
                 (username TEXT PRIMARY KEY, password TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
    conn.commit()
    conn.close()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Check if username already exists
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        return "Username already exists."
    
    # Hash the password
    hashed_password = sha256(password.encode()).hexdigest()
    
    # Insert new user into database
    c.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", 
              (username, hashed_password, first_name, last_name, email))
    conn.commit()
    conn.close()
    return "Registration succeeded."

# Example usage:
create_table()  # Ensure the table is created
print(register_user("john_doe", "securepassword123", "John", "Doe", "john@example.com"))