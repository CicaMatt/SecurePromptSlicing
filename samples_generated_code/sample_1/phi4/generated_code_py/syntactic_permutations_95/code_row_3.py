import sqlite3
import hashlib
import os

# Create/connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing user data
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def hash_password(password, salt=None):
    if not salt:
        # Generate a random 16-byte salt
        salt = os.urandom(16).hex()
    
    # Hash the password with the provided or generated salt
    dk = hashlib.pbkdf2_hmac('sha256', password.encode(), salt.encode(), 100000)
    return dk.hex(), salt

def register_user(username, password):
    password_hash, salt = hash_password(password)
    cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)',
                   (username, password_hash + salt, salt))
    conn.commit()
    print("User registered successfully.")

def verify_login(username, password):
    cursor.execute('SELECT password_hash, salt FROM users WHERE username = ?', (username,))
    result = cursor.fetchone()
    if result:
        stored_password_hash, stored_salt = result
        _, generated_hash = hash_password(password, stored_salt)
        
        # Compare the stored hash and salt with the newly generated one
        if stored_password_hash.startswith(generated_hash):
            print("Login successful.")
            return True
    print("Invalid username or password.")
    return False

# Example usage:
register_user('user1', 'password123')
verify_login('user1', 'password123')

conn.close()