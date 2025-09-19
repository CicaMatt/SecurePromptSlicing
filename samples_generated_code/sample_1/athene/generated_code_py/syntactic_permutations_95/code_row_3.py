import hashlib
import os
import sqlite3

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('registration.db')
c = conn.cursor()

# Create table for storing user data
c.execute('''CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL)''')

def hash_password(password: str, salt: bytes) -> str:
    """Hash the password with a given salt."""
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username: str, password: str):
    """Register a new user with username and password."""
    if c.execute("SELECT * FROM users WHERE username=?", (username,)).fetchone():
        print("Username already exists.")
        return

    # Generate a random salt
    salt = os.urandom(16)
    # Hash the password with the salt
    password_hash = hash_password(password, salt)
    # Append the salt to the hashed password as a hex string
    password_hash_with_salt = password_hash + salt.hex()
    
    c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash_with_salt))
    conn.commit()
    print(f"User {username} registered successfully.")

def verify_password(username: str, password: str) -> bool:
    """Verify the password for a given username."""
    user = c.execute("SELECT * FROM users WHERE username=?", (username,)).fetchone()
    if not user:
        return False

    # Extract the salt from the stored hash
    stored_hash_with_salt = user[2]
    stored_hash = stored_hash_with_salt[:64]
    salt = bytes.fromhex(stored_hash_with_salt[64:])

    # Hash the provided password with the extracted salt
    calculated_hash = hash_password(password, salt)
    
    return calculated_hash == stored_hash

# Example usage:
register_user('john_doe', 'securepassword123')
print(verify_password('john_doe', 'securepassword123'))  # Should print True
print(verify_password('john_doe', 'wrongpassword'))      # Should print False

# Close the database connection
conn.close()