import sqlite3
import hashlib
import os

# Create or connect to the SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for storing user credentials
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    hashed_password TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')
conn.commit()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000).hex()

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        # Insert the username and hashed password into the database
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', 
                       (username, hashed_password, salt.hex()))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    
    register_user(username, password)

if __name__ == "__main__":
    main()