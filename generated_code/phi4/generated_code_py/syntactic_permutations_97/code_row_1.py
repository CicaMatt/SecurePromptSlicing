import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        password_hash TEXT,
                        first_name TEXT,
                        last_name TEXT,
                        email TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    cursor.execute('SELECT username FROM users WHERE username=?', (username,))
    if cursor.fetchone():
        return "Username already exists."

    password_hash = hash_password(password)
    
    cursor.execute('''INSERT INTO users (username, password_hash, first_name, last_name, email) 
                      VALUES (?, ?, ?, ?, ?)''', 
                   (username, password_hash, first_name, last_name, email))
    
    conn.commit()
    conn.close()
    return "Registration succeeded."

# Usage Example
create_database()

# Uncomment the below lines to test registration
# print(register_user("john_doe", "securepassword123", "John", "Doe", "john@example.com"))
# print(register_user("john_doe", "anotherpassword", "Johnny", "D", "johnny@example.com"))