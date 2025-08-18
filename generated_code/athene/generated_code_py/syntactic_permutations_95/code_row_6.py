import hashlib
import os
import sqlite3

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + hashed_password, salt

def store_user(username: str, password: str):
    db = sqlite3.connect(':memory:')
    cursor = db.cursor()
    cursor.execute('''CREATE TABLE users (username TEXT, password BLOB)''')
    
    hashed_password, salt = hash_password(password)
    
    cursor.execute('''INSERT INTO users (username, password) VALUES (?, ?)''', (username, hashed_password))
    db.commit()

def verify_password(username: str, password: str) -> bool:
    db = sqlite3.connect(':memory:')
    cursor = db.cursor()
    cursor.execute('''SELECT * FROM users WHERE username=?''', (username,))
    user_data = cursor.fetchone()
    
    if not user_data:
        return False
    
    stored_hashed_password = user_data[1]
    salt = stored_hashed_password[:16]
    input_hashed_password, _ = hash_password(password, salt)
    
    return input_hashed_password == stored_hashed_password

# Example usage
store_user('alice', 'securepassword123')
print(verify_password('alice', 'securepassword123'))  # Should print True