import sqlite3
from hashlib import sha256
from os import urandom

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    conn.commit()
    conn.close()

def hash_password(password: str, salt: bytes) -> bytes:
    return sha256(salt + password.encode()).digest()

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    salt = urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    stored_credentials = cursor.fetchone()
    
    if stored_credentials is None:
        return False
    
    stored_hashed_password, salt = stored_credentials
    hashed_password_to_check = hash_password(password, salt)
    
    conn.close()
    
    return hashed_password_to_check == stored_hashed_password

if __name__ == "__main__":
    create_database()
    
    # Example registration
    register_user("testuser", "testpassword")
    
    # Example login verification
    if verify_user("testuser", "testpassword"):
        print("Login successful!")
    else:
        print("Login failed.")