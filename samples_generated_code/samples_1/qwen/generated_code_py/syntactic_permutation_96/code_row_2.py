import sqlite3
import hashlib
import os

# Function to create a new user
def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    pwd_hash = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    
    # Combine salt and hashed password
    stored_password = salt + pwd_hash
    
    # Store in database
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password BLOB)''')
    cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, stored_password))
    conn.commit()
    conn.close()

# Example usage
if __name__ == '__main__':
    register_user('exampleuser', 'securepassword123')