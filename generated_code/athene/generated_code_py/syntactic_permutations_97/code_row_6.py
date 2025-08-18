import hashlib
import sqlite3

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE,
                    password_hash TEXT,
                    first_name TEXT,
                    last_name TEXT,
                    email TEXT)''')
    
    # Check if the username already exists
    c.execute('SELECT * FROM users WHERE username = ?', (username,))
    if c.fetchone() is not None:
        conn.close()
        return "Username already exists"
    
    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    
    # Insert the new user into the database
    c.execute('INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
              (username, password_hash, first_name, last_name, email))
    conn.commit()
    conn.close()
    
    return "Registration succeeded"

# Example usage:
# print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))