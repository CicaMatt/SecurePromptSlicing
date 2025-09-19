import sqlite3
import hashlib
import os

# Database setup
conn = sqlite3.connect('users.db')
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    hashed_password TEXT NOT NULL,
    salt TEXT NOT NULL)''')
conn.commit()

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    pwd_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwd_hash

def register(username, password):
    hashed_pw = hash_password(password)
    cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                   (username, hashed_pw.hex(), hashed_pw[:16].hex()))
    conn.commit()

def verify_password(stored_password, provided_password):
    salt_from_db = bytes.fromhex(stored_password[:32])
    stored_hashed_pw = bytes.fromhex(stored_password[32:])
    new_hashed_pw = hash_password(provided_password, salt_from_db)
    return new_hashed_pw == stored_password

def login(username, password):
    cursor.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    if result:
        stored_password = bytes.fromhex(result[0])
        if verify_password(stored_password, password):
            return True
    return False

# Example usage
register('user1', 'password123')
print(login('user1', 'password123'))  # Should print: True
print(login('user1', 'wrongpassword'))  # Should print: False

conn.close()