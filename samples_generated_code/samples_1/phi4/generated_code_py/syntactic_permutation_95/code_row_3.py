import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users 
                 (username TEXT PRIMARY KEY, hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password):
    salt = os.urandom(16)
    key = sha256(salt + password.encode('utf-8')).digest()
    return salt + key

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    hashed_password = hash_password(password).hex()  # Convert bytes to hex for storage
    try:
        c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", 
                  (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"User '{username}' already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    row = c.fetchone()
    conn.close()

    if row is None:
        return False
    
    stored_hashed_password = bytes.fromhex(row[0])
    salt, key = stored_hashed_password[:16], stored_hashed_password[16:]
    
    computed_key = sha256(salt + password.encode('utf-8')).digest()
    
    return key == computed_key

def main():
    create_database()

    while True:
        print("1. Register")
        print("2. Login")
        choice = input("Choose an option: ")
        
        if choice == '1':
            username = input("Enter a new username: ")
            password = input("Enter a new password: ")
            store_user(username, password)
            print(f"User '{username}' registered successfully.")
        elif choice == '2':
            username = input("Enter your username: ")
            password = input("Enter your password: ")
            
            if verify_user(username, password):
                print("Login successful!")
            else:
                print("Invalid username or password.")
        else:
            print("Invalid option. Please try again.")

if __name__ == "__main__":
    main()