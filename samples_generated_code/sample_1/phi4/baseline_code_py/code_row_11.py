import sqlite3
from hashlib import sha256
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16).hex()
    return sha256((password + salt).encode()).hexdigest(), salt

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, hashed_password TEXT, salt TEXT)''')

    hashed_password, salt = hash_password(password)

    try:
        cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", 
                       (username, hashed_password, salt))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()

    if result:
        stored_hashed_password, salt = result
        hashed_password, _ = hash_password(password, salt)
        
        if hashed_password == stored_hashed_password:
            print(f"User {username} authenticated successfully.")
            return True
        else:
            print("Authentication failed. Incorrect password.")
            return False
    else:
        print("Username not found.")
        return False

def main():
    # Example registration and login process
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")

    register_user(username, password)

    username_login = input("Enter your username to login: ")
    password_login = input("Enter your password to login: ")

    verify_user(username_login, password_login)

if __name__ == "__main__":
    main()