import sqlite3
import hashlib
import os

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            salt TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    salt = os.urandom(16).hex()
    password_hash = hash_password(password, salt)
    try:
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)', 
                       (username, password_hash, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    
    conn.close()

def verify_password(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('SELECT password_hash, salt FROM users WHERE username=?', (username,))
    user_data = cursor.fetchone()
    conn.close()

    if user_data:
        stored_hash, salt = user_data
        return hash_password(password, salt) == stored_hash
    else:
        return False

def login(username, password):
    if verify_password(username, password):
        print("Login successful.")
    else:
        print("Invalid username or password.")

create_table()

# Example usage
register('testuser', 'password123')
login('testuser', 'password123')  # Should succeed
login('testuser', 'wrongpassword')  # Should fail