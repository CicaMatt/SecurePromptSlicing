import hashlib
import os
import sqlite3

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    key = hashlib.pbkdf2_hmac(
        'sha256',
        password.encode('utf-8'),
        salt,
        100000
    )
    return key

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password BLOB, salt BLOB)''')

    salt = generate_salt()
    hashed_password = hash_password(password, salt)

    c.execute("INSERT INTO users VALUES (?, ?, ?)", (username, hashed_password, salt))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    store_user(username, password)