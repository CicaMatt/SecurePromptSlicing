import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 username TEXT PRIMARY KEY,
                 salt TEXT NOT NULL,
                 hashed_password TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def generate_salt(length=16):
    return os.urandom(length).hex()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Check if username already exists
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        print("Username already exists.")
        return
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
              (username, salt, hashed_password))
    
    conn.commit()
    conn.close()
    print("User registered successfully.")

def main():
    create_database()
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    register_user(username, password)

if __name__ == "__main__":
    main()