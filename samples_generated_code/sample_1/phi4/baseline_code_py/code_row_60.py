import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.sha256(salt.encode() + password.encode()).hexdigest()

def generate_salt():
    return os.urandom(16).hex()

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        hashed_password TEXT,
                        salt TEXT)''')
    conn.commit()
    conn.close()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Check if the user already exists
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    if cursor.fetchone():
        raise ValueError("Username already exists")
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                   (username, hashed_password + salt, salt))
    
    conn.commit()
    conn.close()

create_database()

# Example usage:
try:
    username_input = input("Enter a new username: ")
    password_input = input("Enter a new password: ")
    register_user(username_input, password_input)
    print("User registered successfully!")
except ValueError as e:
    print(e)