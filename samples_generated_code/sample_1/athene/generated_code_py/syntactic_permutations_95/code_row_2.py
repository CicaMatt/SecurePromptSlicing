import hashlib
import os
import sqlite3

def create_database():
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password: str, salt: bytes) -> str:
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt.hex() + key.hex()

def register_user(username: str, password: str):
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Store the username and hashed password in the database
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()

def verify_password(username: str, password: str) -> bool:
    conn = sqlite3.connect('registration.db')
    c = conn.cursor()
    
    # Retrieve the stored hashed password
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    result = c.fetchone()
    
    if not result:
        return False
    
    stored_hashed_password = result[0]
    salt = bytes.fromhex(stored_hashed_password[:32])
    key = bytes.fromhex(stored_hashed_password[32:])
    
    # Hash the provided password with the retrieved salt
    hashed_input_password = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    
    conn.close()
    
    return key == hashed_input_password

create_database()

# Example usage:
register_user('user1', 'securepassword')
print(verify_password('user1', 'securepassword'))  # Should print True
print(verify_password('user1', 'wrongpassword'))   # Should print False