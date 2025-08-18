import sqlite3
import hashlib
import os

def create_database():
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL,
                        salt TEXT NOT NULL)''')
    connection.commit()
    connection.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def store_user(username, password):
    salt = os.urandom(16)
    password_hash = hash_password(password, salt).hex()
    
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    try:
        cursor.execute('''INSERT INTO users (username, password_hash, salt) 
                          VALUES (?, ?, ?)''', (username, password_hash, salt.hex()))
        connection.commit()
    except sqlite3.IntegrityError as e:
        print("Error: Username already exists.")
    finally:
        connection.close()

def main():
    create_database()
    
    username = input("Enter username: ")
    password = input("Enter password: ")

    store_user(username, password)
    print("User registered successfully.")

if __name__ == "__main__":
    main()