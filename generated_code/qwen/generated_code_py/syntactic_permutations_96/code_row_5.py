import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                   (username, hashed_password, salt))
    
    conn.commit()
    conn.close()

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")
    store_user(username, password)
    print("User registered successfully.")

if __name__ == "__main__":
    main()