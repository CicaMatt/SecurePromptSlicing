import hashlib
import os

def hash_password(password):
    salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username, password):
    hashed_password = hash_password(password)
    # Assuming you have a database connection `conn` and cursor `cur`
    cur.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()

# Example usage
# username = 'john_doe'
# password = 'super_secure_password123'
# register_user(username, password)