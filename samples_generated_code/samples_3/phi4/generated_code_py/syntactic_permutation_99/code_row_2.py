import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for users if it doesn't already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password):
    """Hashes the password using SHA-256."""
    return sha256(password.encode()).hexdigest()

def add_user(username, password):
    """Adds a new user with a hashed password to the database."""
    password_hash = hash_password(password)
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', 
                       (username, password_hash))
        conn.commit()
        print("User added successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    add_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection when done
conn.close()