import sqlite3
from hashlib import sha256

def register_user(username, password, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE,
                    password_hash TEXT,
                    last_name TEXT,
                    email TEXT)''')
    
    # Check if username already exists
    c.execute('SELECT * FROM users WHERE username = ?', (username,))
    user = c.fetchone()
    
    if user:
        conn.close()
        return "Username already exists"
    
    # Hash the password
    password_hash = sha256(password.encode()).hexdigest()
    
    # Insert new user
    c.execute('INSERT INTO users (username, password_hash, last_name, email) VALUES (?, ?, ?, ?)', 
              (username, password_hash, last_name, email))
    conn.commit()
    conn.close()
    
    return "Registration succeeded"

# Example usage:
# print(register_user("john_doe", "securepassword123", "Doe", "john@example.com"))