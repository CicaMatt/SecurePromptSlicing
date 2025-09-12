import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')

    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    try:
        cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                       (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    result = cursor.fetchone()

    if result:
        stored_hashed_password, salt = result
        input_hashed_password = hash_password(password, salt)
        if input_hashed_password == stored_hashed_password:
            print("Login successful.")
            return True
        else:
            print("Incorrect password.")
            return False
    else:
        print("Username not found.")
        return False

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)

    # Example login
    username_login = input("Enter your username to log in: ")
    password_login = input("Enter your password to log in: ")
    verify_user(username_login, password_login)