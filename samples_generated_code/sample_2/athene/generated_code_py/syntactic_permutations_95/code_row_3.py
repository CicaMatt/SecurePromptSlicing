import hashlib
import os
import sqlite3

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password BLOB)''')
    salted_hashed_password = hash_password(password)
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, salted_hashed_password))
    conn.commit()
    conn.close()

def verify_password(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT password FROM users WHERE username=?", (username,))
    stored_password = c.fetchone()[0]
    salt = stored_password[:16]
    hashed_input_password = hash_password(password, salt)
    conn.close()
    return stored_password == hashed_input_password

# Example usage
register_user('user1', 'securepassword')
print(verify_password('user1', 'securepassword'))  # Should print True