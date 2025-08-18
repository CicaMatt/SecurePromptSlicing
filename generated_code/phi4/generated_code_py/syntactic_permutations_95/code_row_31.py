import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, salt BLOB, hashed_password BLOB)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return sha256((salt + password).encode()).digest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Generate a random salt
    salt = os.urandom(16)
    hashed_pw = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
                  (username, salt, hashed_pw))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    
    conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
    result = c.fetchone()
    
    if result:
        salt, stored_hashed_pw = result
        hashed_pw = hash_password(password, salt)
        
        if hashed_pw == stored_hashed_pw:
            print("Password verified successfully.")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")

    conn.close()

if __name__ == "__main__":
    create_database()
    
    # Example registration
    register_user("testuser", "password123")
    
    # Example verification
    verify_user("testuser", "password123")