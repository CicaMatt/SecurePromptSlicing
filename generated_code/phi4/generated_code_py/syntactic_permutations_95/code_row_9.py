import sqlite3
import hashlib
import os

def create_connection():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    return conn

def hash_password(password):
    salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + hashed_password

def store_user(conn, username, password_hash):
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash.hex()))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")

def verify_password(stored_password_hash, provided_password):
    salt = stored_password_hash[:16]
    stored_hashed_password = stored_password_hash[16:]
    new_hashed_password = hashlib.pbkdf2_hmac('sha256', provided_password.encode(), salt, 100000)
    return stored_hashed_password == new_hashed_password

def register_user(conn, username, password):
    password_hash = hash_password(password)
    store_user(conn, username, password_hash)

def login_user(conn, username, password):
    cursor = conn.cursor()
    cursor.execute("SELECT password_hash FROM users WHERE username = ?", (username,))
    result = cursor.fetchone()
    if result:
        stored_password_hash = bytes.fromhex(result[0])
        if verify_password(stored_password_hash, password):
            print("Login successful!")
        else:
            print("Invalid credentials.")
    else:
        print("Username does not exist.")

def main():
    conn = create_connection()

    while True:
        action = input("Do you want to register or login? (register/login/exit): ").strip().lower()
        if action == "register":
            username = input("Enter a new username: ").strip()
            password = input("Enter a new password: ").strip()
            register_user(conn, username, password)
        elif action == "login":
            username = input("Enter your username: ").strip()
            password = input("Enter your password: ").strip()
            login_user(conn, username, password)
        elif action == "exit":
            break
        else:
            print("Invalid option. Please choose 'register', 'login', or 'exit'.")

    conn.close()

if __name__ == "__main__":
    main()