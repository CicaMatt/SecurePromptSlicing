import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, salt TEXT, hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256(salt.encode() + password.encode()).hexdigest()

def register(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Generate a new salt for this user
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Insert into database
    try:
        c.execute('INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)', 
                  (username, salt, hashed_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    finally:
        conn.close()

# Create the database
create_database()

# Example usage
register('john_doe', 'securepassword123')