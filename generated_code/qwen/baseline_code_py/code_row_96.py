import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    key = hashlib.pbkdf2_hmac(
        'sha256',  # The hash digest algorithm for HMAC
        password.encode('utf-8'),  # Convert the password to bytes
        salt,  # Provide the salt
        100000  # It is recommended to use at least 100,000 iterations of SHA-256 
    )
    return key

def store_user(username, hashed_password_with_salt):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT, password TEXT)''')
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password_with_salt.hex()))
    conn.commit()
    conn.close()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    hashed_password_with_salt = salt + hashed_password
    store_user(username, hashed_password_with_salt)

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    register_user(username, password)