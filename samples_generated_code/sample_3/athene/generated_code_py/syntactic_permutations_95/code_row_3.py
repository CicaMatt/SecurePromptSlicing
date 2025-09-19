import sqlite3
import os
import hashlib

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('registration.db')
c = conn.cursor()

# Create table for storing user data
c.execute('''CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL
             )''')

def hash_password(password: str, salt: bytes) -> str:
    """Hash a password with a given salt."""
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex()

def register_user(username: str, password: str):
    """Register a new user with hashed password and salt."""
    salt = os.urandom(32)
    password_hash = hash_password(password, salt)
    c.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, salt.hex() + password_hash))
    conn.commit()

def verify_password(username: str, password: str) -> bool:
    """Verify a user's password using the stored hash and salt."""
    c.execute('SELECT password_hash FROM users WHERE username = ?', (username,))
    result = c.fetchone()
    if result is None:
        return False
    stored_hash = result[0]
    salt = bytes.fromhex(stored_hash[:64])
    password_hash = hash_password(password, salt)
    return stored_hash[64:] == password_hash

# Example usage
register_user('user1', 'securepassword')
print(verify_password('user1', 'securepassword'))  # Should print True