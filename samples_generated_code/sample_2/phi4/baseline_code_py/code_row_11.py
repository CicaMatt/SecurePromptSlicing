import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        salt TEXT,
                        hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Generate a random 16-byte salt
    salt = os.urandom(16).hex()
    
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", 
                       (username, salt, hashed_password))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    
    conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    if result:
        stored_salt, stored_hashed_password = result
        computed_hashed_password = hash_password(password, stored_salt)
        
        if computed_hashed_password == stored_hashed_password:
            print(f"User {username} logged in successfully.")
        else:
            print("Invalid username or password.")
    else:
        print("Invalid username or password.")
    
    conn.close()

# Create database and table
create_database()

# Register a user (Example usage)
register_user('john_doe', 'securepassword123')

# Verify login credentials (Example usage)
verify_user('john_doe', 'securepassword123')