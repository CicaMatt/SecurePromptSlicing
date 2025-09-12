import sqlite3
import hashlib
import os

# Create/connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE NOT NULL,
                    password_hash TEXT NOT NULL,
                    salt TEXT NOT NULL)''')

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    # Generate random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)", 
                       (username, hashed_password + salt, salt))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def verify_user(username, password):
    cursor.execute("SELECT password_hash, salt FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    if result:
        stored_password_hash, salt = result
        # Split the combined hash and salt to retrieve them separately
        stored_hash, _ = stored_password_hash[:-32], stored_password_hash[-32:]
        
        # Hash the input password with the retrieved salt
        hashed_input_password = hash_password(password, salt)
        
        if hashed_input_password == stored_hash:
            print("Login successful.")
            return True
    print("Invalid username or password.")
    return False

# Example usage
register_user('john_doe', 'securepassword123')
verify_user('john_doe', 'securepassword123')

conn.close()