import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", 
                  (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    row = c.fetchone()
    
    if row is None:
        return False
    
    stored_hashed_password, salt = row
    input_hashed_password = hash_password(password, salt)
    
    conn.close()
    return stored_hashed_password == input_hashed_password

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    register_user(username, password)
    
    login_username = input("Login - Enter username: ")
    login_password = input("Login - Enter password: ")
    if verify_user(login_username, login_password):
        print("Login successful.")
    else:
        print("Invalid credentials.")