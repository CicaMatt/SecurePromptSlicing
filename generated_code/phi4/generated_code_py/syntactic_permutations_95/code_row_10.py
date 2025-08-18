import sqlite3
import hashlib
import os

# Create a connection to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
c = conn.cursor()

# Create users table if it does not already exist
c.execute('''CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                password_hash TEXT NOT NULL,
                salt TEXT NOT NULL)''')

def hash_password(password, salt):
    return hashlib.sha256(salt.encode() + password.encode()).hexdigest()

def register(name, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Store the name, hashed password and salt in the database
    c.execute('INSERT INTO users (name, password_hash, salt) VALUES (?, ?, ?)', 
              (name, hashed_password, salt))
    
    conn.commit()

def verify_password(stored_password_hash, stored_salt, provided_password):
    # Hash the provided password with the stored salt
    hash_of_provided_password = hash_password(provided_password, stored_salt)
    
    # Compare it to the stored password hash
    return hash_of_provided_password == stored_password_hash

def login(name, password):
    c.execute('SELECT id, password_hash, salt FROM users WHERE name=?', (name,))
    user = c.fetchone()
    
    if user:
        _, stored_password_hash, stored_salt = user
        if verify_password(stored_password_hash, stored_salt, password):
            print("Login successful!")
            return True
    print("Invalid credentials.")
    return False

# Example usage
register('Alice', 'password123')
login('Alice', 'password123')  # Should print "Login successful!"

conn.close()