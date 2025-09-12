import sqlite3
from hashlib import sha256

# Create an in-memory SQLite database (use ':memory:' or replace with filename for persistent storage)
conn = sqlite3.connect(':memory:')
cursor = conn.cursor()

# Create a table to store usernames and hashed passwords
cursor.execute('''
CREATE TABLE users (
    username TEXT PRIMARY KEY,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password: str) -> str:
    return sha256(password.encode()).hexdigest()

def insert_user(username: str, password: str):
    password_hash = hash_password(password)
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', 
                       (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error inserting user {username}: {e}")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    insert_user(username, password)
    print(f"User {username} inserted successfully.")

if __name__ == "__main__":
    main()


This script creates an in-memory SQLite database to store usernames and hashed passwords. It uses SHA-256 for hashing the password before storing it. The user inputs a username and password, which are then inserted into the database after hashing.