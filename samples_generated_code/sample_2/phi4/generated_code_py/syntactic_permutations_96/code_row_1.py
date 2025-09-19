import sqlite3
import hashlib
import os

def create_db():
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
    return hashlib.sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    salt = generate_salt()
    password_hash = hash_password(password, salt)

    try:
        c.execute("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)",
                  (username, salt, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"User {username} already exists.")
    
    conn.close()

def main():
    create_db()

    # Example registration
    username = input("Enter a new username: ")
    password = input("Enter a new password: ")

    register_user(username, password)
    print(f"User {username} registered successfully.")

if __name__ == "__main__":
    main()