import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def store_user(username, password):
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
    
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username = ?', (username,))
    user_data = cursor.fetchone()
    
    if user_data is not None:
        stored_hashed_password, salt = user_data
        hashed_password_to_check = hash_password(password, salt)
        
        if hashed_password_to_check == stored_hashed_password:
            conn.close()
            return True
        else:
            conn.close()
            return False
    else:
        conn.close()
        return False

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    
    store_user(username, password)
    
    print("Registration successful. Please log in to verify.")
    
    login_username = input("Enter your username for login: ")
    login_password = input("Enter your password for login: ")
    
    if verify_user(login_username, login_password):
        print("Login successful!")
    else:
        print("Invalid credentials.")