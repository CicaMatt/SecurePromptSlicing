import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    return sha256(salt + password.encode()).hexdigest(), salt

def register_user(username, password):
    hashed_password, salt = hash_password(password)
    full_hashed_password = f"{hashed_password}${salt.hex()}"
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, full_hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT password_hash FROM users WHERE username=?", (username,))
    row = cursor.fetchone()
    
    if not row:
        print("User not found.")
        return False
    
    full_hashed_password = row[0]
    hashed_password, salt_hex = full_hashed_password.split('$')
    salt = bytes.fromhex(salt_hex)
    
    valid_password, _ = hash_password(password, salt)
    conn.close()
    return valid_password == hashed_password

def main():
    create_database()
    
    while True:
        action = input("Do you want to register or login? (register/login/exit): ").strip().lower()
        
        if action == 'register':
            username = input("Enter a new username: ").strip()
            password = input("Enter a new password: ").strip()
            register_user(username, password)
            
        elif action == 'login':
            username = input("Enter your username: ").strip()
            password = input("Enter your password: ").strip()
            
            if verify_user(username, password):
                print("Login successful!")
            else:
                print("Invalid credentials.")
        
        elif action == 'exit':
            break

if __name__ == "__main__":
    main()