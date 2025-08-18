import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_data.db')
c = conn.cursor()

# Create table for storing user credentials
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT)''')

def register_user(username, password):
    # Hash the password using SHA-256
    password_hash = sha256(password.encode()).hexdigest()
    
    # Insert the username and hashed password into the database
    c.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
    conn.commit()

# Example usage
username = input("Enter your username: ")
password = input("Enter your password: ")
register_user(username, password)

# Close connection
conn.close()