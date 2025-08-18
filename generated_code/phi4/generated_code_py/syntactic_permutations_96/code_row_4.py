import sqlite3
import hashlib
import os

# Create or connect to the SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing user data if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    salt TEXT,
    hashed_password TEXT
)
''')

def generate_salt():
    return os.urandom(16).hex()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    # Check if the username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    if cursor.fetchone():
        print("Username already exists.")
        return False

    # Generate salt and hash password
    salt = generate_salt()
    hashed_password = hash_password(password, salt)

    # Store user data in the database
    cursor.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)',
                   (username, salt, hashed_password))
    conn.commit()
    print("User registered successfully.")
    return True

def main():
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    register_user(username, password)

if __name__ == '__main__':
    main()

# Close the database connection when done
conn.close()