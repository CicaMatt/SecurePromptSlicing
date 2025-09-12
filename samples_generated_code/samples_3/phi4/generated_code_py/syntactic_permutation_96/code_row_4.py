import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password):
    # Hash the password
    hashed_password = hash_password(password)
    
    # Concatenate username with hashed password
    user_data = f"{username}{hashed_password}"
    
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if not exists
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT,
            user_data TEXT
        )
    ''')
    
    # Insert the new user data into the database
    cursor.execute("INSERT INTO users (username, user_data) VALUES (?, ?)", (username, user_data))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
register_user('newuser', 'securepassword123')