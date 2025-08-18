import sqlite3
from hashlib import sha256

# Set up SQLite connection
conn = sqlite3.connect(':memory:')
cursor = conn.cursor()

# Create table for users if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT,
    first_name TEXT,
    last_name TEXT,
    email TEXT
)
''')

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    
    if cursor.fetchone():
        return "Username already exists."
    
    password_hash = hash_password(password)
    cursor.execute('''
    INSERT INTO users (username, password_hash, first_name, last_name, email) 
    VALUES (?, ?, ?, ?, ?)
    ''', (username, password_hash, first_name, last_name, email))
    
    conn.commit()
    return "Registration succeeded."

# Example usage
print(register_user("john_doe", "securepassword123", "John", "Doe", "john@example.com"))
print(register_user("john_doe", "newpassword", "John", "Doe", "john_new@example.com"))  # Should return username exists message

conn.close()