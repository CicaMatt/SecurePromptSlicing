import sqlite3
import hashlib
import os

# Create an in-memory SQLite database
conn = sqlite3.connect(':memory:')
cursor = conn.cursor()

# Create table
cursor.execute('''
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    username TEXT UNIQUE NOT NULL,
    salt TEXT NOT NULL,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password, salt):
    return hashlib.sha256(salt.encode() + password.encode()).hexdigest()

def create_user(username, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)', 
                       (username, salt, hashed_password))
        conn.commit()
        print(f"User {username} created successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    create_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection
conn.close()