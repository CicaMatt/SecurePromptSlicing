import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')
    hashed_password = hash_password(password)
    salt = 'somesalt'
    final_hashed = salt + hashed_password
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, final_hashed))
    conn.commit()
    conn.close()