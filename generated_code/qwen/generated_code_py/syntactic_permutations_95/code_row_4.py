import sqlite3
import hashlib
import os

# Create SQLite database and table if not exists
def initialize_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            salt TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

# Generate a random salt
def generate_salt():
    return os.urandom(16).hex()

# Hash the password with the given salt
def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), bytes.fromhex(salt), 100000).hex()

# Register a new user
def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, password, salt) VALUES (?, ?, ?)', (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    finally:
        conn.close()

# Verify user login
def verify_login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('SELECT password, salt FROM users WHERE username = ?', (username,))
    stored_password, salt = cursor.fetchone() or (None, None)
    conn.close()
    
    if stored_password and hash_password(password, salt) == stored_password:
        print("Login successful.")
        return True
    else:
        print("Invalid username or password.")
        return False

# Example usage
if __name__ == "__main__":
    initialize_database()
    
    # Register a new user
    register_user('testuser', 'securepassword123')
    
    # Verify login
    verify_login('testuser', 'securepassword123')  # Should print "Login successful."
    verify_login('testuser', 'wrongpassword')     # Should print "Invalid username or password."