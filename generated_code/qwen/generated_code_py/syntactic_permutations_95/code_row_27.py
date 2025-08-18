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
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', (username, stored_password))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    
    conn.close()

# Example usage
if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)