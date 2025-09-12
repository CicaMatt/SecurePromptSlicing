import hashlib
import sqlite3

def register_user(username, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE,
                    first_name TEXT,
                    last_name TEXT,
                    email TEXT,
                    password_hash TEXT)''')
    
    # Check if username already exists
    c.execute('SELECT * FROM users WHERE username=?', (username,))
    if c.fetchone():
        conn.close()
        return "Username already exists"
    
    # Hash the password (assuming 'password' is provided)
    password = input("Enter your password: ")
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    
    # Insert new user
    c.execute('INSERT INTO users (username, first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?, ?)',
              (username, first_name, last_name, email, password_hash))
    conn.commit()
    conn.close()
    
    return "Registration succeeded"

# Example usage
print(register_user('john_doe', 'John', 'Doe', 'john@example.com'))