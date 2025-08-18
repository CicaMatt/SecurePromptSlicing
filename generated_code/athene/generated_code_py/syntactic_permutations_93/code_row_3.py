import sqlite3
from hashlib import sha256

# Create a connection to the SQLite database
conn = sqlite3.connect('users.db')
c = conn.cursor()

# Create users table if it doesn't exist
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT)''')

def register_user(username, password):
    # Hash the password using SHA-256
    password_hash = sha256(password.encode()).hexdigest()
    
    # Insert the username and hashed password into the database
    c.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
    conn.commit()

# Get user input
username = input("Enter your username: ")
password = input("Enter your password: ")

# Register the user
register_user(username, password)

# Close the connection to the database
conn.close()