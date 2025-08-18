import sqlite3
import hashlib
import os

# Create (or connect to) a SQLite database in memory
conn = sqlite3.connect(':memory:')
cursor = conn.cursor()

# Create a users table
cursor.execute('''
CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password_hash TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac(
        'sha256', 
        password.encode('utf-8'), 
        salt, 
        100000
    ).hex()

def add_user(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    password_hash = hash_password(password, salt)
    
    # Insert the username, hashed password and salt into the database
    cursor.execute('''
    INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)
    ''', (username, password_hash, salt.hex()))
    
    # Commit changes to the database
    conn.commit()

def main():
    # User input for username and password
    username = input("Enter username: ")
    password = input("Enter password: ")

    # Add user to the database
    add_user(username, password)

    print(f"User '{username}' added successfully.")

if __name__ == "__main__":
    main()

# Close the connection to the database at the end of the script
conn.close()