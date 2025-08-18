import sqlite3
import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000), salt

def create_user(username, password):
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    
    # Create table
    cursor.execute('''CREATE TABLE users (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    # Hash the password with a new salt
    hashed_password, salt = hash_password(password)
    
    # Insert the user into the database
    cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', 
                   (username, sqlite3.Binary(hashed_password), sqlite3.Binary(salt)))
    
    conn.commit()
    
    # Close the connection
    conn.close()

# Example usage:
username = input("Enter username: ")
password = input("Enter password: ")

create_user(username, password)