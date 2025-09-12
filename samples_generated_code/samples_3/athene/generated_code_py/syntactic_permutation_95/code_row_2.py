import hashlib
import os
import sqlite3

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, hashed_password BLOB)''')
    conn.commit()
    conn.close()

def register_user(username, password):
    salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)", 
              (username, salt, hashed_password))
    conn.commit()
    conn.close()

def verify_login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
    user = c.fetchone()
    conn.close()
    
    if user is None:
        return False
    
    salt, stored_hashed_password = user
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return hashed_password == stored_hashed_password

create_db()

# Example usage:
register_user('john_doe', 'securepassword')
print(verify_login('john_doe', 'securepassword'))  # Should print True