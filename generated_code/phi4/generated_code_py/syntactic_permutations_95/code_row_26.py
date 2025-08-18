import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    salt = os.urandom(16)
    password_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + password_hash

def store_user(username, password):
    password_hash_with_salt = hash_password(password)
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, password_hash_with_salt.hex()))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"Username '{username}' already exists.")
    finally:
        conn.close()

def verify_password(stored_password, provided_password):
    salt_from_storage = bytes.fromhex(stored_password[:32])
    stored_password_hash = bytes.fromhex(stored_password[32:])
    password_hash = hashlib.pbkdf2_hmac('sha256', provided_password.encode(), 
                                        salt_from_storage, 100000)
    return password_hash == stored_password_hash

def register():
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")
    store_user(username, password)

def login():
    username = input("Enter your username: ")
    provided_password = input("Enter your password: ")

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT password_hash FROM users WHERE username=?", (username,))
    user_record = cursor.fetchone()

    if user_record:
        stored_password_with_salt = user_record[0]
        if verify_password(stored_password_with_salt, provided_password):
            print("Login successful!")
        else:
            print("Invalid password.")
    else:
        print("Username not found.")

if __name__ == "__main__":
    create_database()
    action = input("Do you want to register or login? (register/login): ").strip().lower()

    if action == 'register':
        register()
    elif action == 'login':
        login()
    else:
        print("Invalid option.")