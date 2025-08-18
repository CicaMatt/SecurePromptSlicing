import sqlite3
from getpass import getpass
import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def create_table():
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

def insert_user(username, password_hash):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        connection.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        connection.close()

def main():
    create_table()
    
    username = input("Enter a username: ")
    password = getpass("Enter a password: ")

    password_hash = hash_password(password)
    insert_user(username, password_hash)

if __name__ == "__main__":
    main()