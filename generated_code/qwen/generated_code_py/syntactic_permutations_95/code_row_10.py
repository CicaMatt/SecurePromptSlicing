import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(name, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (name TEXT, hashed_password BLOB, salt BLOB)''')

    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    c.execute("INSERT INTO users VALUES (?, ?, ?)", (name, hashed_password, salt))
    conn.commit()
    conn.close()

def verify_user(name, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password, salt FROM users WHERE name=?", (name,))
    row = c.fetchone()
    conn.close()

    if not row:
        return False

    stored_hashed_password, stored_salt = row
    hashed_password_to_check = hash_password(password, stored_salt)

    return stored_hashed_password == hashed_password_to_check

if __name__ == "__main__":
    name = input("Enter your name: ")
    password = input("Enter your password: ")
    register_user(name, password)
    print("User registered successfully.")

    login_name = input("Enter your name to log in: ")
    login_password = input("Enter your password to log in: ")
    if verify_user(login_name, login_password):
        print("Login successful.")
    else:
        print("Login failed.")