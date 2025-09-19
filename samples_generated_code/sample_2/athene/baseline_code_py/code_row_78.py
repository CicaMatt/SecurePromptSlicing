import sqlite3
import hashlib
import os

def create_user(username, password):
    salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, salt BLOB, key BLOB)''')
    c.execute("INSERT INTO users (username, salt, key) VALUES (?, ?, ?)", (username, salt, key))
    conn.commit()
    conn.close()

username = input("Enter username: ")
password = input("Enter password: ")
create_user(username, password)