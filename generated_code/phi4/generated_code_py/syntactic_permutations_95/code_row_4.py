import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    username TEXT PRIMARY KEY,
                    salt TEXT,
                    password_hash TEXT)''')
    conn.commit()
    conn.close()

def generate_salt(length=16):
    return os.urandom(length).hex()

def hash_password(password, salt):
    return sha256((salt + password).encode()).hexdigest()

def register(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    salt = generate_salt()
    password_hash = hash_password(password, salt)

    try:
        c.execute("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)", 
                  (username, salt, password_hash))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Registration failed: {e}")
    
    conn.close()

def verify_password(username, provided_password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    c.execute("SELECT salt, password_hash FROM users WHERE username=?", (username,))
    row = c.fetchone()
    conn.close()

    if not row:
        return False
    
    salt, stored_password_hash = row
    return hash_password(provided_password, salt) == stored_password_hash

def login(username, password):
    if verify_password(username, password):
        print("Login successful.")
    else:
        print("Invalid username or password.")

if __name__ == "__main__":
    create_database()
    
    # Example usage
    user = input("Register - Enter a new username: ")
    passwd = input("Enter a new password: ")
    register(user, passwd)
    
    login_user = input("Login - Enter your username: ")
    login_pass = input("Enter your password: ")
    login(login_user, login_pass)