import sqlite3
from hashlib import sha256

# Function to hash password
def hash_password(password):
    return sha256(password.encode()).hexdigest()

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_data.db')
cursor = conn.cursor()

# Create table for storing user data if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS users
             (username TEXT, password_hash TEXT)''')

# Get username and password from user input
username = input("Enter your username: ")
password = input("Enter your password: ")

# Hash the password
hashed_password = hash_password(password)

# Insert the username and hashed password into the database
cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, hashed_password))

# Commit changes and close the connection
conn.commit()
conn.close()