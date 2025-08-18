import sqlite3
import hashlib
import os

# Create or connect to a SQLite database file
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing user data
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)', 
                       (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def verify_user(username, password):
    cursor.execute('SELECT password_hash, salt FROM users WHERE username = ?', (username,))
    user = cursor.fetchone()

    if not user:
        return False

    stored_password_hash, salt = user
    hashed_input_password = hash_password(password, salt)

    return hashed_input_password == stored_password_hash

# Example usage
register_user('example_user', 'securepassword123')
is_valid = verify_user('example_user', 'securepassword123')
print("Password valid:", is_valid)

# Close the connection when done
conn.close()