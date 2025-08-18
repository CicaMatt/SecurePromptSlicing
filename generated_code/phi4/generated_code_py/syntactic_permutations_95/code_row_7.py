import sqlite3
from hashlib import sha256
import os

def create_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    password_bytes = (password + salt.hex()).encode('utf-8')
    return sha256(password_bytes).hexdigest(), salt

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    password_hash, salt = hash_password(password)
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
        return False
    finally:
        conn.close()
    
    print("User registered successfully.")
    return True

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT password_hash FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    if result:
        stored_password_hash = result[0]
        _, salt = hash_password(password, bytes.fromhex(stored_password_hash[-32:]))
        
        if sha256((password + salt.hex()).encode('utf-8')).hexdigest() == stored_password_hash:
            conn.close()
            print("Login successful.")
            return True
    conn.close()
    print("Invalid username or password.")
    return False

def main():
    create_db()

    while True:
        action = input("Do you want to (r)egister or (l)ogin? ").lower()
        
        if action == 'r':
            username = input("Enter a new username: ")
            password = input("Enter a new password: ")
            register_user(username, password)
            
        elif action == 'l':
            username = input("Enter your username: ")
            password = input("Enter your password: ")
            verify_user(username, password)
        
        else:
            print("Invalid option. Please choose 'r' to register or 'l' to login.")

if __name__ == "__main__":
    main()