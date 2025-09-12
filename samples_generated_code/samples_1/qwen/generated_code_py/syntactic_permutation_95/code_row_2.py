import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

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
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT hashed_password, salt FROM users WHERE username = ?", (username,))
    stored_data = c.fetchone()
    
    if stored_data:
        stored_hashed_password, stored_salt = stored_data
        input_hashed_password = hash_password(password, stored_salt)
        
        if stored_hashed_password == input_hashed_password:
            print("Login successful.")
            return True
        else:
            print("Incorrect password.")
            return False
    else:
        print("Username not found.")
        return False

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    register_user(username, password)
    
    login_username = input("Enter username for login: ")
    login_password = input("Enter password for login: ")
    
    verify_user(login_username, login_password)