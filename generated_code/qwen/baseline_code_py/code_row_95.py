import sqlite3
import hashlib
import os

# Function to create the database and table if they don't exist
def initialize_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, password TEXT)''')
    conn.commit()
    conn.close()

# Function to generate a random salt
def generate_salt():
    return os.urandom(16)

# Function to hash the password with the given salt
def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

# Function to register a new user
def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Generate a salt and hash the password
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    # Combine the salt and hashed password
    stored_password = salt.hex() + ':' + hashed_password
    
    try:
        cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, stored_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different one.")
    finally:
        conn.close()

# Function to verify user login
def verify_login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Retrieve the stored salt and hashed password from the database
    cursor.execute('SELECT password FROM users WHERE username = ?', (username,))
    result = cursor.fetchone()
    
    if result:
        stored_password = result[0]
        salt, db_hashed_password = stored_password.split(':')
        
        # Hash the provided password with the retrieved salt and compare to the stored hash
        salt_bytes = bytes.fromhex(salt)
        new_hashed_password = hash_password(password, salt_bytes)
        
        if new_hashed_password == db_hashed_password:
            print("Login successful.")
            return True
        else:
            print("Incorrect password.")
            return False
    else:
        print("Username not found.")
        return False

# Initialize the database
initialize_database()

# Example usage of registration and login functions
register_user('testuser', 'testpassword')
verify_login('testuser', 'testpassword')