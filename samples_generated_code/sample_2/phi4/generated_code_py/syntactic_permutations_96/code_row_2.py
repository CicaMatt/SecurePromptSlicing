import sqlite3
from hashlib import pbkdf2_hmac
import os

# Create/connect to SQLite database
conn = sqlite3.connect('users.db')
c = conn.cursor()

# Create table if it doesn't exist
c.execute('''CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                salt BLOB,
                hashed_password BLOB)''')

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with PBKDF2 (HMAC-SHA256), using the generated salt
    hashed_password = pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    
    # Store username, salt, and hashed password in the database
    c.execute("INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?)",
              (username, salt, hashed_password))
    
    conn.commit()

def check_user(username, password):
    c.execute("SELECT salt, hashed_password FROM users WHERE username = ?", (username,))
    user_data = c.fetchone()
    
    if user_data:
        stored_salt, stored_hashed_password = user_data
        # Hash the provided password with the stored salt
        test_hashed_password = pbkdf2_hmac('sha256', password.encode(), stored_salt, 100000)
        
        # Compare the hashed passwords
        return test_hashed_password == stored_hashed_password
    
    return False

# Example usage:
register_user("exampleUser", "examplePassword")
print(check_user("exampleUser", "examplePassword"))  # Should print: True
print(check_user("exampleUser", "wrongPassword"))   # Should print: False

conn.close()