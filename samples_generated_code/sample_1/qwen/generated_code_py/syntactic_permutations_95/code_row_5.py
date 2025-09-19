import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')

    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    try:
        cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    cursor.execute("SELECT hashed_password, salt FROM users WHERE username = ?", (username,))
    result = cursor.fetchone()
    conn.close()

    if result:
        stored_hashed_password, salt = result
        provided_hashed_password = hash_password(password, salt)
        return stored_hashed_password == provided_hashed_password
    else:
        return False

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    register_user(username, password)

    login_username = input("Enter your username to log in: ")
    login_password = input("Enter your password to log in: ")

    if verify_user(login_username, login_password):
        print("Login successful.")
    else:
        print("Invalid credentials.")