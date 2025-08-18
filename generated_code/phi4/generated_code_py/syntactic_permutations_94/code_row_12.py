import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for users if it doesn't already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    hashed_password TEXT NOT NULL
)
''')

def hash_password(password):
    """Hash a password for storing."""
    return sha256(password.encode('utf-8')).hexdigest()

def register_user(username, password):
    """Register a new user by hashing the password and inserting into database."""
    hashed_password = hash_password(password)
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', (username, hashed_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Error: Username already exists.")

def main():
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    
    register_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection to the database
conn.close()