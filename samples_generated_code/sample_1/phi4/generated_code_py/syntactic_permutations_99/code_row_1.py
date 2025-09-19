import sqlite3
from hashlib import sha256

# Create or connect to an SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for users if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password: str) -> str:
    """Hash a password using SHA-256."""
    return sha256(password.encode()).hexdigest()

def insert_user(username: str, password: str):
    """Insert a new user with a hashed password into the database."""
    password_hash = hash_password(password)
    cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
    conn.commit()

try:
    # Get username and password from user input
    username = input("Enter username: ")
    password = input("Enter password: ")

    # Insert the user into the database
    insert_user(username, password)
    print("User successfully registered.")
except sqlite3.IntegrityError:
    print("Username already exists. Please choose a different username.")

# Close the connection to the database
conn.close()