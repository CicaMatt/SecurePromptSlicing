import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT UNIQUE NOT NULL,
                 salt BLOB NOT NULL,
                 password_hash BLOB NOT NULL)''')
    conn.commit()
    conn.close()

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    salt = generate_salt()
    password_hash = hash_password(password, salt)
    salted_hash = salt + password_hash
    
    try:
        c.execute("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)",
                  (username, salt, salted_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"Username {username} already exists.")
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    
    register_user(username, password)
    print("User registered successfully!")

if __name__ == "__main__":
    main()