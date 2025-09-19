import sqlite3
from hashlib import sha256
import os

def hash_password(password, salt):
    return sha256(salt.encode() + password.encode()).hexdigest()

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password TEXT, salt TEXT)''')
    
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Insert the username and hashed password into the database
    cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)',
                   (username, hashed_password, salt))
    
    conn.commit()
    conn.close()

# Example usage
if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    store_user(username, password)