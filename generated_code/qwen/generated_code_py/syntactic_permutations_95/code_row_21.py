import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def create_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password BLOB, salt BLOB)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT password, salt FROM users WHERE username = ?", (username,))
    row = c.fetchone()
    
    if row is None:
        conn.close()
        return False
    
    stored_password, salt = row
    hashed_password = hash_password(password, salt)
    
    conn.close()
    return hashlib.compare_digest(stored_password, hashed_password)

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    
    create_user(username, password)
    
    print("\nVerifying user...")
    login_username = input("Enter your username to log in: ")
    login_password = input("Enter your password to log in: ")
    
    if verify_user(login_username, login_password):
        print("Login successful!")
    else:
        print("Invalid username or password.")