import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    hasher = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return hasher

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    with sqlite3.connect("users.db") as conn:
        cursor = conn.cursor()
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                hashed_password BLOB,
                salt BLOB
            )
        """)
        cursor.execute(
            "INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
            (username, hashed_password, salt)
        )

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    register_user(username, password)