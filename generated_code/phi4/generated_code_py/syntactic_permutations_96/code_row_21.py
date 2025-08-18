import sqlite3
import hashlib
import os

# Create or connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for storing user information if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    salt TEXT NOT NULL,
                    hashed_password TEXT NOT NULL)''')

def hash_password(password, salt):
    return hashlib.sha256(salt.encode() + password.encode()).hexdigest()

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)',
                       (username, salt, hashed_password))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def main():
    # Example usage
    username = input("Enter username: ")
    password = input("Enter password: ")

    register_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection to the database when done
conn.close()