import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing user credentials if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT
)
''')

def hash_password(password: str) -> str:
    return sha256(password.encode()).hexdigest()

def insert_user(username: str, password: str):
    password_hash = hash_password(password)
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        conn.commit()
        print(f"User {username} inserted successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    insert_user(username, password)

if __name__ == "__main__":
    main()

# Close the database connection
conn.close()