import sqlite3
import hashlib
import os

def create_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT UNIQUE NOT NULL,
                 salt BLOB NOT NULL,
                 hashed_password BLOB NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def generate_salt():
    return os.urandom(16)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    try:
        c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
                  (username, salt, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    finally:
        conn.close()

def main():
    create_table()
    
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")

    register_user(username, password)
    print("User registered successfully!")

if __name__ == "__main__":
    main()