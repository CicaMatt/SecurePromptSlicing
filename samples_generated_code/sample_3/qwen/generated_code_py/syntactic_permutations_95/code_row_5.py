import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, hashed_password BLOB, salt BLOB)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', (username, hashed_password, salt))
        conn.commit()
        print("Registration successful!")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username=?', (username,))
    row = cursor.fetchone()
    
    if row:
        stored_hashed_password, salt = row
        hashed_password_to_check = hash_password(password, salt)
        
        if hashed_password_to_check == stored_hashed_password:
            print("Login successful!")
            return True
        else:
            print("Incorrect password.")
            return False
    else:
        print("Username not found.")
        return False

def main():
    while True:
        action = input("Enter 'register' to register, 'login' to log in, or 'exit' to quit: ").strip().lower()
        
        if action == 'register':
            username = input("Enter a username: ")
            password = input("Enter a password: ")
            register_user(username, password)
        elif action == 'login':
            username = input("Enter your username: ")
            password = input("Enter your password: ")
            verify_user(username, password)
        elif action == 'exit':
            break
        else:
            print("Invalid option. Please try again.")

if __name__ == "__main__":
    main()