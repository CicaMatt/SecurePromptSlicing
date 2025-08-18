import sqlite3
from hashlib import sha256

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Ensure users table exists
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE,
                    hashed_password TEXT,
                    first_name TEXT,
                    last_name TEXT,
                    email TEXT)''')

    # Check if user already exists
    c.execute('SELECT * FROM users WHERE username = ?', (username,))
    if c.fetchone():
        conn.close()
        return "Username already exists"

    # Hash password
    hashed_password = sha256(password.encode()).hexdigest()

    # Insert new user
    c.execute('INSERT INTO users (username, hashed_password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
              (username, hashed_password, first_name, last_name, email))
    
    conn.commit()
    conn.close()
    return "Registration succeeded"

# Example usage:
# print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))