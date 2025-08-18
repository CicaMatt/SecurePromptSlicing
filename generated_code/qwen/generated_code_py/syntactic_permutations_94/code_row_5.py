import sqlite3
from hashlib import pbkdf2_hmac
from os import urandom

def hash_password(password, salt):
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')

    salt = urandom(16)
    hashed_password = hash_password(password, salt)

    try:
        cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                       (username, hashed_password, salt))
        conn.commit()
        print("User inserted successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    insert_user(username, password)