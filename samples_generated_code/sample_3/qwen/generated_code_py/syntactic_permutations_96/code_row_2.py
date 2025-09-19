import sqlite3
from hashlib import sha256
import os

def hash_password(password, salt):
    return sha256(salt.encode() + password.encode()).hexdigest()

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Store the username and salted-hashed password in the database
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, salted_hashed_password TEXT)''')
    c.execute("INSERT INTO users (username, salted_hashed_password) VALUES (?, ?)", (username, salt + hashed_password))
    conn.commit()
    conn.close()

# Example usage
register_user('exampleuser', 'examplepassword')