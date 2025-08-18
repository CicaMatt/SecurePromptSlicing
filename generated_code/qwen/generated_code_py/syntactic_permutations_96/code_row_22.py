import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Concatenate salt and hashed password
    stored_password = salt + hashed_password
    
    # Store in database (example using SQLite)
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password BLOB)''')
    
    try:
        c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, stored_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

# Example usage
register_user('exampleuser', 'securepassword123')