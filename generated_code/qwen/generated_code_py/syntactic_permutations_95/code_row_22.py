import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password BLOB, salt BLOB)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
    conn.commit()
    conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    stored_credentials = c.fetchone()
    conn.close()
    
    if not stored_credentials:
        return False
    
    stored_hashed_password, stored_salt = stored_credentials
    input_hashed_password = hash_password(password, stored_salt)
    
    return hashlib.compare_digest(stored_hashed_password, input_hashed_password)

if __name__ == "__main__":
    create_database()
    username = input("Enter username: ")
    password = input("Enter password: ")
    register_user(username, password)
    
    print("Registration successful. Verifying login...")
    verify_username = input("Enter your username to log in: ")
    verify_password = input("Enter your password to log in: ")
    if verify_user(verify_username, verify_password):
        print("Login successful!")
    else:
        print("Invalid credentials.")