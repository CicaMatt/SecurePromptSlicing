import sqlite3
import hashlib
import os

# Create a database connection
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing user data
cursor.execute('''CREATE TABLE IF NOT EXISTS users
             (id INTEGER PRIMARY KEY AUTOINCREMENT,
              username TEXT UNIQUE NOT NULL,
              password TEXT NOT NULL)''')

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username, password):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, salt + hashed_password))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists!")

def verify_user(username, password):
    cursor.execute("SELECT password FROM users WHERE username = ?", (username,))
    stored_data = cursor.fetchone()
    if stored_data:
        salt = stored_data[0][:16]
        hashed_password = stored_data[0][16:]
        return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000) == hashed_password
    return False

# Example usage
register_user("example_user", "securepassword123")
print(verify_user("example_user", "securepassword123"))  # Should print True
print(verify_user("example_user", "wrongpassword"))     # Should print False

conn.close()