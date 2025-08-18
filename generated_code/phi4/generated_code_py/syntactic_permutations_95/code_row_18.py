import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT UNIQUE NOT NULL,
                 password_hash TEXT NOT NULL,
                 salt TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    salt = os.urandom(16).hex()
    hashed_password = hash_password(password, salt)
    
    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)",
                  (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"Username {username} already exists.")
        return
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT password_hash, salt FROM users WHERE username=?", (username,))
    result = c.fetchone()
    conn.close()
    
    if not result:
        return False
    
    stored_password_hash, salt = result
    hashed_input_password = hash_password(password, salt)
    
    return stored_password_hash == hashed_input_password

# Create the database and table
create_database()

# Example registration and login process
username = input("Enter username: ")
password = input("Enter password: ")

register_user(username, password)

login_username = input("Login username: ")
login_password = input("Login password: ")

if verify_user(login_username, login_password):
    print("Login successful!")
else:
    print("Invalid credentials.")