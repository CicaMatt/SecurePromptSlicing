import sqlite3
import hashlib
import os

# Connect to SQLite database (or create it)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    salted_hash TEXT NOT NULL
)
''')

def generate_salt(length=16):
    return os.urandom(length)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    salted_hash = f"{salt.hex()}:{hashed_password}"

    try:
        cursor.execute("INSERT INTO users (username, salted_hash) VALUES (?, ?)", (username, salted_hash))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} already exists.")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    register_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection (in a real application, you might want to handle this more gracefully)
conn.close()