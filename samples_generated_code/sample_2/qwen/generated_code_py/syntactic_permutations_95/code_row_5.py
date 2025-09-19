import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)',
                       (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username=?', (username,))
    stored_credentials = cursor.fetchone()
    
    if stored_credentials:
        stored_hashed_password, salt = stored_credentials
        input_hashed_password = hash_password(password, salt)
        
        if input_hashed_password == stored_hashed_password:
            return True
        else:
            return False
    else:
        return False

if __name__ == "__main__":
    print("Registering a new user:")
    username = input("Enter username: ")
    password = input("Enter password: ")
    register_user(username, password)
    
    print("\nVerifying user login:")
    username = input("Enter username: ")
    password = input("Enter password: ")
    if verify_user(username, password):
        print("Login successful.")
    else:
        print("Invalid credentials.")