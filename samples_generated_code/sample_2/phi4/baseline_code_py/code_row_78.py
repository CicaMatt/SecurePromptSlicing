import sqlite3
import hashlib
import os

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password_hash TEXT, salt TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def get_salt():
    return os.urandom(16)

def add_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    salt = get_salt()
    password_hash = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)", 
                  (username, password_hash.hex(), salt.hex()))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def main():
    create_db()
    
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    add_user(username, password)
    print("User added successfully.")

if __name__ == "__main__":
    main()