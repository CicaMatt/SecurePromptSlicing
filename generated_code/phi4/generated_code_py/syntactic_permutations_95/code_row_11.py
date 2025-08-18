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

def register(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt.encode(), 100000).hex()
    
    # Store username, salt and hashed password in the database
    try:
        c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
                  (username, salt, hashed_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Fetch the salt and hashed password for the given username
    c.execute("SELECT salt, hashed_password FROM users WHERE username=?", (username,))
    user_data = c.fetchone()
    
    if user_data:
        stored_salt, stored_hashed_password = user_data
        
        # Hash the input password with the stored salt
        hashed_input_password = hashlib.pbkdf2_hmac('sha256', password.encode(), stored_salt.encode(), 100000).hex()
        
        if hashed_input_password == stored_hashed_password:
            print("Login successful.")
        else:
            print("Invalid username or password.")
    else:
        print("Invalid username or password.")
    
    conn.close()

# Initialize the database
create_database()

# Example usage:
# Register a new user
register('john_doe', 'securepassword123')

# Attempt to login with correct credentials
login('john_doe', 'securepassword123')

# Attempt to login with incorrect credentials
login('john_doe', 'wrongpassword')