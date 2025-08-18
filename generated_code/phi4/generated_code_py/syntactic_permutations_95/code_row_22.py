import sqlite3
import hashlib
import os

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
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt.encode(), 100000).hex()

def register_user(username, password):
    salt = os.urandom(16).hex()
    password_hash = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)",
                       (username, password_hash, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"User {username} already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT password_hash, salt FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    if not result:
        print(f"User {username} does not exist.")
        return False
    
    stored_password_hash, salt = result
    password_hash = hash_password(password, salt)
    
    if password_hash == stored_password_hash:
        print("Login successful!")
        return True
    else:
        print("Invalid username or password.")
        return False

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
            verify_user(username, password)
        
        elif action == 'exit':
            break
        
        else:
            print("Invalid option. Please choose 'register', 'login', or 'exit'.")

if __name__ == "__main__":
    main()