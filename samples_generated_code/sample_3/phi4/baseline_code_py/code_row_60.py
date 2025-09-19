import hashlib
import os
import sqlite3

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    pwdhash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwdhash

def register_user(username, password, conn):
    salted_hash = hash_password(password)
    cursor = conn.cursor()
    query = "INSERT INTO users (username, password) VALUES (?, ?)"
    cursor.execute(query, (username, salted_hash.hex()))
    conn.commit()

def setup_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT)")
    conn.commit()
    return conn

if __name__ == "__main__":
    connection = setup_database()

    try:
        # Example registration
        user_username = input("Enter a username: ")
        user_password = input("Enter a password: ")

        register_user(user_username, user_password, connection)
        print(f"User {user_username} registered successfully.")
    finally:
        connection.close()