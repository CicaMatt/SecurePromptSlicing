import sqlite3
import hashlib
import os

# Create a database connection
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for storing user data
cursor.execute('''CREATE TABLE IF NOT EXISTS users
             (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT)''')
conn.commit()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username, password):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, salt.hex() + hashed_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def verify_user(username, password):
    cursor.execute("SELECT password FROM users WHERE username = ?", (username,))
    stored_password_info = cursor.fetchone()
    if stored_password_info:
        salt_hex, hashed_password_stored = stored_password_info[0][:32], stored_password_info[0][32:]
        salt = bytes.fromhex(salt_hex)
        hashed_password_provided = hash_password(password, salt)
        if hashed_password_provided == hashed_password_stored:
            print("Login successful.")
            return True
    print("Invalid username or password.")
    return False

# Example usage
register_user('testuser', 'securepassword123')
verify_user('testuser', 'securepassword123')