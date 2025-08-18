import sqlite3
import os
import hashlib

def register_user(username, password):
    db = sqlite3.connect('users.db')
    cursor = db.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT, salt TEXT)''')

    # Generate a random salt
    salt = os.urandom(16).hex()

    # Hash the password with the salt
    password_salt = salt + password
    password_hash = hashlib.sha256(password_salt.encode()).hexdigest()

    # Store username, hashed password, and salt in the database
    cursor.execute('''INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)''', (username, password_hash, salt))
    db.commit()
    db.close()

def verify_password(username, password):
    db = sqlite3.connect('users.db')
    cursor = db.cursor()
    cursor.execute('''SELECT password_hash, salt FROM users WHERE username=?''', (username,))
    user_data = cursor.fetchone()
    db.close()

    if not user_data:
        return False

    stored_password_hash, salt = user_data
    password_salt = salt + password
    password_hash = hashlib.sha256(password_salt.encode()).hexdigest()

    return password_hash == stored_password_hash