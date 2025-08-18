import sqlite3
from hashlib import pbkdf2_hmac
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password_hash TEXT, salt BLOB)''')
    conn.commit()
    conn.close()

def hash_password(password: str, salt: bytes) -> bytes:
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def generate_salt() -> bytes:
    return os.urandom(16)

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)",
                  (username, password_hash.hex(), salt))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Registration failed: {e}")
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter username: ")
    password = input("Enter password: ")

    register_user(username, password)
    print("User registered successfully.")

if __name__ == "__main__":
    main()