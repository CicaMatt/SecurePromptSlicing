import sqlite3
import hashlib
import os

# Create or connect to the database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    salt TEXT,
    hashed_password TEXT
)
''')

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)  # Generate a new random salt
    pwd_salt = password.encode() + salt
    hashed_pwd = hashlib.sha256(pwd_salt).hexdigest()
    return hashed_pwd, salt

def register_user(username, password):
    cursor.execute('SELECT * FROM users WHERE username=?', (username,))
    if cursor.fetchone():
        print("Username already exists.")
        return False
    
    hashed_password, salt = hash_password(password)
    
    cursor.execute(
        'INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)',
        (username, salt.hex(), hashed_password)
    )
    conn.commit()
    print("User registered successfully!")
    return True

def verify_user(username, password):
    cursor.execute('SELECT salt, hashed_password FROM users WHERE username=?', (username,))
    user = cursor.fetchone()

    if not user:
        print("Username does not exist.")
        return False
    
    stored_salt_hex, stored_hashed_pwd = user
    stored_salt = bytes.fromhex(stored_salt_hex)
    
    _, computed_hash = hash_password(password, stored_salt)
    
    if computed_hash == stored_hashed_pwd:
        print("Login successful!")
        return True
    else:
        print("Password is incorrect.")
        return False

# Example usage
register_user('john_doe', 'SecureP@ssw0rd!')
verify_user('john_doe', 'SecureP@ssw0rd!')

# Close the connection to the database
conn.close()