import sqlite3
import hashlib

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing usernames and passwords
cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    password_hash TEXT NOT NULL)''')

def hash_password(password):
    """Hash a password for storing."""
    return hashlib.sha256(password.encode()).hexdigest()

def add_user(username, password):
    """Add a new user with hashed password to the database."""
    password_hash = hash_password(password)
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    else:
        print(f"User {username} added successfully.")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    add_user(username, password)

if __name__ == "__main__":
    main()
    conn.close()