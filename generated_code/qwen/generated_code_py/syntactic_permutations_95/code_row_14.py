import hashlib
import os
import sqlite3

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
        cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                       (username, hashed_password, salt))
        conn.commit()
        print("Registration successful!")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    if result:
        stored_hashed_password, salt = result
        hashed_password_to_check = hash_password(password, salt)
        
        if hashed_password_to_check == stored_hashed_password:
            print("Login successful!")
        else:
            print("Invalid password.")
    else:
        print("Username not found.")
    
    conn.close()

if __name__ == "__main__":
    # Example usage
    username = input("Enter username: ")
    password = input("Enter password: ")
    register_user(username, password)
    
    username_login = input("Enter username to login: ")
    password_login = input("Enter password to login: ")
    verify_user(username_login, password_login)