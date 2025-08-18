import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex()

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, hashed_password TEXT)''')

    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    # Store the salted and hashed password
    full_hashed_password = salt.hex() + hashed_password
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', (username, full_hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    store_user(username, password)

if __name__ == "__main__":
    main()