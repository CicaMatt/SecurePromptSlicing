import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def create_db():
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE users (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    return conn

def register_user(conn, username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                       (username, hashed_password, salt))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} already exists.")

def main():
    conn = create_db()

    # Example usage
    username = "testuser"
    password = "securepassword123"

    register_user(conn, username, password)

    conn.close()

if __name__ == "__main__":
    main()