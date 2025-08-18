import hashlib
import sqlite3
import os

# Create or connect to an SQLite database
conn = sqlite3.connect('user_database.db')
cursor = conn.cursor()

# Create a table if it does not exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    hashed_password TEXT NOT NULL
)
''')

def hash_password(password):
    # Generate a random salt
    salt = os.urandom(16)
    # Combine the password and salt
    pwd_salt_combo = password.encode() + salt
    # Hash the combination using SHA-256
    hashed = hashlib.pbkdf2_hmac('sha256', pwd_salt_combo, salt, 100000)
    # Return a tuple of salt and hashed password
    return salt + hashed

def insert_user(username, password):
    # Hash the user's password
    hashed_password = hash_password(password)
    # Convert bytes to hexadecimal string for storage
    hashed_password_hex = hashed_password.hex()
    try:
        # Insert username and hashed password into the database
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', (username, hashed_password_hex))
        conn.commit()
        print("User added successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

# Example usage
username = input("Enter username: ")
password = input("Enter password: ")
insert_user(username, password)

# Close the database connection
conn.close()