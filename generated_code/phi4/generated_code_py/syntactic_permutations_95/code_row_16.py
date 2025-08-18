import sqlite3
import hashlib
import os
from getpass import getpass

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        salt TEXT NOT NULL,
                        hashed_password TEXT NOT NULL
                    )''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()

def register_user():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    username = input("Enter username: ")
    while True:
        try:
            cursor.execute("SELECT * FROM users WHERE username=?", (username,))
            if cursor.fetchone() is not None:
                print("Username already exists. Try another.")
                username = input("Enter username: ")
            else:
                break
        except sqlite3.IntegrityError:
            print("Username already exists. Try another.")
            username = input("Enter username: ")

    password = getpass("Enter password: ")
    
    salt = os.urandom(16).hex()
    hashed_password = hash_password(password, salt)
    
    cursor.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
                   (username, salt, hashed_password))
    conn.commit()
    print("User registered successfully.")
    conn.close()

def login_user():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    username = input("Enter username: ")
    password = getpass("Enter password: ")

    cursor.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        salt, stored_hashed_password = user
        hashed_password = hash_password(password, salt)
        
        if hashed_password == stored_hashed_password:
            print("Login successful!")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")

    conn.close()

def main():
    create_database()
    
    while True:
        choice = input("Do you want to register or login? (register/login): ").strip().lower()
        
        if choice == 'register':
            register_user()
        elif choice == 'login':
            login_user()
        else:
            print("Invalid choice. Please choose 'register' or 'login'.")
        
        again = input("Do you want to continue? (yes/no): ").strip().lower()
        if again != 'yes':
            break

if __name__ == '__main__':
    main()