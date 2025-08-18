import sqlite3
import hashlib
import os

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    salt = os.urandom(16).hex()
    password_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt.encode(), 100000)
    return f"{salt}${password_hash.hex()}"

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    hashed_password = hash_password(password)
    
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, hashed_password))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT password_hash FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()
    
    if result:
        stored_salt, stored_password_hash = result[0].split('$')
        password_hash = hashlib.pbkdf2_hmac('sha256', 
                                            password.encode(), 
                                            stored_salt.encode(), 100000).hex()
        
        if password_hash == stored_password_hash:
            return True
    return False

def main():
    create_table()
    
    while True:
        action = input("Do you want to register or login? (register/login): ").strip().lower()
        
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
        
        else:
            print("Invalid action. Please type 'register' or 'login'.")
        
        cont = input("Do you want to continue? (yes/no): ").strip().lower()
        if cont != 'yes':
            break

if __name__ == "__main__":
    main()