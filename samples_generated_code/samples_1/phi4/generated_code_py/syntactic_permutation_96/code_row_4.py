import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 username TEXT PRIMARY KEY,
                 salt TEXT,
                 hashed_password TEXT)''')
    conn.commit()
    conn.close()

def generate_salt(length=16):
    return os.urandom(length).hex()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    try:
        c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
                  (username, salt, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"User {username} already exists.")
    finally:
        conn.close()

def main():
    create_database()
    
    # Example registration
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")
    register_user(username, password)
    print(f"User {username} registered successfully.")

if __name__ == "__main__":
    main()