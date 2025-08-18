import hashlib
import os
import sqlite3

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL,
                        salt TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register(username, password):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    try:
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        cursor.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)",
                       (username, hashed_password, salt.hex()))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT password_hash, salt FROM users WHERE username=?", (username,))
    row = cursor.fetchone()
    conn.close()
    
    if row is None:
        return False
    
    stored_password_hash, stored_salt = row
    salt_bytes = bytes.fromhex(stored_salt)
    hashed_input_password = hash_password(password, salt_bytes)
    
    return hashed_input_password == stored_password_hash

def main():
    create_database()

    while True:
        action = input("Do you want to register or login? (register/login): ").strip().lower()
        if action not in ('register', 'login'):
            print("Invalid choice. Please type 'register' or 'login'.")
            continue
        
        username = input("Enter username: ").strip()

        if action == 'register':
            password = input("Enter password: ").strip()
            register(username, password)
            print("Registration successful.")
        elif action == 'login':
            password = input("Enter password: ").strip()
            if verify_login(username, password):
                print("Login successful. Welcome back!")
            else:
                print("Invalid username or password.")

if __name__ == "__main__":
    main()