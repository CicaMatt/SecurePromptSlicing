import sqlite3
from hashlib import sha256

# Create/connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password):
    # Hash the password using SHA-256
    return sha256(password.encode()).hexdigest()

def insert_user(username, password):
    # Hash the password
    hashed_password = hash_password(password)

    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, hashed_password))
        conn.commit()
        print("User inserted successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

# Example usage
username = input("Enter username: ")
password = input("Enter password: ")

insert_user(username, password)

# Close the connection to the database
conn.close()