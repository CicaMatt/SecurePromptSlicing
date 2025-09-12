import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes) -> str:
    key = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return key.hex()

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT UNIQUE, password TEXT, salt BLOB)''')

    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    try:
        c.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)",
                  (username, hashed_password, salt))
    except sqlite3.IntegrityError:
        print('Username already exists.')
    else:
        conn.commit()
        print(f'User {username} registered successfully.')

    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT password, salt FROM users WHERE username=?", (username,))
    row = c.fetchone()
    
    if row is None:
        return False

    stored_password, salt = row
    hashed_password = hash_password(password, salt)
    conn.close()

    return hashed_password == stored_password

# Example usage
register_user('testuser', 'securepassword123')
print(verify_password('testuser', 'securepassword123'))