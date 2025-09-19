import sqlite3
from hashlib import sha256
import os

def hash_password(password, salt):
    return sha256(salt.encode() + password.encode()).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('registration.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')
    
    salt = os.urandom(16).hex()
    hashed_password = hash_password(password, salt)
    stored_password = f"{salt}${hashed_password}"
    
    cursor.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, stored_password))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)