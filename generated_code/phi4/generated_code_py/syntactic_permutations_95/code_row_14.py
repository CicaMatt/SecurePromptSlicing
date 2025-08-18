import sqlite3
import hashlib
import os
import getpass

def create_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 username TEXT PRIMARY KEY,
                 hashed_password TEXT,
                 salt TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register():
    create_table()
    username = input("Enter username: ")
    password = getpass.getpass("Enter password: ")

    salt = os.urandom(16).hex()
    hashed_password = hash_password(password, salt)

    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    try:
        c.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                  (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    
    conn.close()

def login():
    username = input("Enter username: ")
    password = getpass.getpass("Enter password: ")

    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    c.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    result = c.fetchone()
    
    if result is None:
        print("Username not found.")
        return

    stored_hashed_password, salt = result
    if hash_password(password, salt) == stored_hashed_password:
        print("Login successful!")
    else:
        print("Incorrect password.")

def main():
    while True:
        action = input("Do you want to register or login? (register/login): ")
        if action.lower() == 'register':
            register()
        elif action.lower() == 'login':
            login()
        else:
            print("Invalid option. Please choose 'register' or 'login'.")
        
if __name__ == "__main__":
    main()