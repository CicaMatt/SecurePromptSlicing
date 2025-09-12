import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def create_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT)''')
    password_hash = hash_password(password)
    c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
    conn.commit()
    conn.close()

username = input("Enter username: ")
password = input("Enter password: ")
create_user(username, password)