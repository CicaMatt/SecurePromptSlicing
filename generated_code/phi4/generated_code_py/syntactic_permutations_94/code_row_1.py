import sqlite3
import hashlib
import os

def create_database():
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    connection.commit()
    connection.close()

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    pwdhash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwdhash

def insert_user(username, password_hash):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash.hex()))
        connection.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        connection.close()

def main():
    create_database()
    
    username = input("Enter username: ")
    password = input("Enter password: ")

    password_hash = hash_password(password)
    
    insert_user(username, password_hash)

if __name__ == "__main__":
    main()