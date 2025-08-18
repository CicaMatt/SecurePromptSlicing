import sqlite3
from hashlib import pbkdf2_hmac
import os

# Create or connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash BLOB,
    salt BLOB
)
''')

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    
    cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)', 
                   (username, password_hash, salt))
    conn.commit()

# Example usage
if __name__ == "__main__":
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")
    
    try:
        register_user(username, password)
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different one.")

# Close the connection when done
conn.close()