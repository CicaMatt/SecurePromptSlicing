import sqlite3
from hashlib import sha256
from os import urandom

def create_user(username, password):
    salt = urandom(16)
    hash_password = sha256(password.encode() + salt).hexdigest()
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hash BLOB, salt BLOB)''')
    c.execute("INSERT INTO users (username, hash, salt) VALUES (?, ?, ?)", (username, hash_password, salt))
    conn.commit()
    conn.close()

# Example usage
create_user('john_doe', 'supersecurepassword123')