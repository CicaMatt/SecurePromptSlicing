import sqlite3
import hashlib
import os

# Database setup
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

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def generate_salt():
    return os.urandom(16).hex()

def register_user(username, password):
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    try:
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)', 
                       (username, password_hash, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def login_user(username, password):
    cursor.execute('SELECT password_hash, salt FROM users WHERE username = ?', (username,))
    result = cursor.fetchone()
    
    if result:
        stored_password_hash, salt = result
        if hash_password(password, salt) == stored_password_hash:
            print("Login successful.")
        else:
            print("Invalid password.")
    else:
        print("Username not found.")

# Example usage
register_user('testuser', 'password123')
login_user('testuser', 'password123')

conn.close()