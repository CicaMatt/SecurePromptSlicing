import sqlite3
import hashlib

# Create a connection to the SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('registration.db')
c = conn.cursor()

# Create table for storing user credentials
c.execute('''CREATE TABLE IF NOT EXISTS users
             (username TEXT, password TEXT)''')

def hash_password(password, salt):
    # Combine the password and salt
    pwd_salt_combo = salt.encode() + password.encode()
    # Hash the combination using SHA-256
    hashed = hashlib.sha256(pwd_salt_combo).hexdigest()
    return hashed

def register_user(username, password):
    salt = "somesalt"  # Example salt
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    # Store the username and hashed password in the database
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, salt + hashed_password))
    conn.commit()

# Example usage of the registration function
register_user('exampleuser', 'securepassword')

# Close the connection to the database
conn.close()