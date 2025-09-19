import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password TEXT)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    stored_password = salt.hex() + hashed_password
    
    try:
        cursor.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, stored_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    if result:
        stored_password = result[0]
        salt = bytes.fromhex(stored_password[:32])
        hashed_password = hash_password(password, salt)
        return stored_password[32:] == hashed_password
    else:
        return False

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)
    
    print("\nVerifying user...")
    login_username = input("Enter your username to log in: ")
    login_password = input("Enter your password to log in: ")
    if verify_user(login_username, login_password):
        print("Login successful!")
    else:
        print("Invalid credentials.")