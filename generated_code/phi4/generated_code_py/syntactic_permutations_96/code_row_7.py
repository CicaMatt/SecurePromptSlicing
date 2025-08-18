import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
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
    cursor = conn.cursor()

    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)",
                       (username, salt, hashed_password))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} is already taken.")
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    register_user(username, password)

if __name__ == "__main__":
    main()