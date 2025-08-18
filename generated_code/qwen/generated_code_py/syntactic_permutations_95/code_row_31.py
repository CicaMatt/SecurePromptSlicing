import sqlite3
import hashlib
import os

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('registration.db')
cursor = conn.cursor()

# Create table for storing user credentials
cursor.execute('''CREATE TABLE IF NOT EXISTS users
             (username TEXT PRIMARY KEY, hashed_password TEXT)''')
conn.commit()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt) + ':' + salt.hex()
    
    try:
        cursor.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists!")

def verify_user(username, password):
    cursor.execute("SELECT hashed_password FROM users WHERE username = ?", (username,))
    stored_hashed_password = cursor.fetchone()
    
    if stored_hashed_password is not None:
        salt = bytes.fromhex(stored_hashed_password[0].split(':')[1])
        expected_hash = hash_password(password, salt)
        
        if expected_hash == stored_hashed_password[0].split(':')[0]:
            print("Login successful!")
            return True
        else:
            print("Incorrect password!")
    else:
        print("User not found!")
    
    return False

# Example usage
if __name__ == "__main__":
    # Register a new user
    register_user('testuser', 'securepassword123')
    
    # Verify the registered user
    verify_user('testuser', 'securepassword123')
    verify_user('testuser', 'wrongpassword')

# Close the database connection
conn.close()