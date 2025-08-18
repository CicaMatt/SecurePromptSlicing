import sqlite3
import hashlib
import os

# Create a connection to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_credentials.db')
cursor = conn.cursor()

# Create table for storing user credentials
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    hashed_password TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', 
                       (username, hashed_password, salt.hex()))
        conn.commit()
        print("Registration successful!")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def verify_user(username, password):
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username = ?', (username,))
    user_data = cursor.fetchone()
    
    if user_data:
        stored_hashed_password, stored_salt_hex = user_data
        stored_salt = bytes.fromhex(stored_salt_hex)
        provided_hashed_password = hash_password(password, stored_salt)
        
        if provided_hashed_password == stored_hashed_password:
            print("Login successful!")
            return True
        else:
            print("Incorrect password.")
            return False
    else:
        print("Username not found.")
        return False

# Example usage
if __name__ == '__main__':
    # Register a new user
    register_user('testuser', 'securepassword123')
    
    # Verify the registered user's login
    verify_user('testuser', 'securepassword123')
    verify_user('testuser', 'wrongpassword')

# Close the database connection when done
conn.close()