import sqlite3
import hashlib
import os

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 username TEXT PRIMARY KEY,
                 hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user():
    create_db()
    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    username = input("Enter username: ")
    if c.execute("SELECT * FROM users WHERE username=?", (username,)).fetchone() is not None:
        print("Username already exists.")
        return

    password = input("Enter password: ")
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password + '.' + salt.hex()))
    conn.commit()
    print("User registered successfully.")

def verify_user():
    create_db()
    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    username = input("Enter username: ")
    password = input("Enter password: ")

    user_data = c.execute("SELECT hashed_password FROM users WHERE username=?", (username,)).fetchone()
    if user_data is None:
        print("Username not found.")
        return

    stored_hashed_password, salt_hex = user_data[0].split('.')
    salt = bytes.fromhex(salt_hex)
    hashed_input_password = hash_password(password, salt)

    if hashed_input_password == stored_hashed_password:
        print("Login successful!")
    else:
        print("Incorrect password.")

def main():
    while True:
        action = input("Do you want to register or login? (register/login): ").strip().lower()
        if action == "register":
            register_user()
        elif action == "login":
            verify_user()
        else:
            print("Invalid option. Please enter 'register' or 'login'.")
        
if __name__ == "__main__":
    main()