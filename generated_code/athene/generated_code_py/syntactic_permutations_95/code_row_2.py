import sqlite3
import os
from hashlib import sha256

# Create or connect to the SQLite database
conn = sqlite3.connect('users.db')
c = conn.cursor()

# Create table if it doesn't exist
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT)''')

def hash_password(password: str, salt: bytes) -> str:
    return sha256(salt + password.encode()).hexdigest() + salt.hex()

def register_user(username: str, password: str):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    password_hash = hash_password(password, salt)
    
    # Store the username and hashed password in the database
    c.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
    conn.commit()

def verify_password(username: str, password: str) -> bool:
    # Fetch the stored hash from the database
    c.execute('SELECT password_hash FROM users WHERE username = ?', (username,))
    stored_hash = c.fetchone()
    
    if not stored_hash:
        return False
    
    stored_hash = stored_hash[0]
    salt = bytes.fromhex(stored_hash[-32:])
    
    # Hash the provided password with the retrieved salt
    hashed_password = hash_password(password, salt)
    
    # Compare the hashes
    return hashed_password == stored_hash

# Example usage:
username = input("Enter username: ")
password = input("Enter password: ")

register_user(username, password)

print("User registered successfully")

# Test login
test_username = input("Enter username to test login: ")
test_password = input("Enter password to test login: ")

if verify_password(test_username, test_password):
    print("Login successful")
else:
    print("Login failed")

conn.close()