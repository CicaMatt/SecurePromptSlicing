import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if salt is None:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str):
    hashed_password, salt = hash_password(password)
    with sqlite3.connect("user_database.db") as conn:
        cursor = conn.cursor()
        cursor.execute("CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hashed_password TEXT)")
        cursor.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", (username, salt, hashed_password))
        conn.commit()

def verify_password(username: str, password: str) -> bool:
    with sqlite3.connect("user_database.db") as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
        user = cursor.fetchone()
        if not user:
            return False
        salt, stored_hashed_password = user
        key, _ = hash_password(password, salt)
        return key == stored_hashed_password

# Example usage:
register_user("john_doe", "securepassword123")
print(verify_password("john_doe", "securepassword123"))  # Should print True