import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_data.db')
c = conn.cursor()

# Create table for storing user data
c.execute('''CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL)''')

def register_user(username, password):
    # Hash the password using SHA-256
    password_hash = sha256(password.encode()).hexdigest()
    
    try:
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
        print('User registered successfully.')
    except sqlite3.IntegrityError:
        print('Username already exists.')

# Get username and password from user input
username = input('Enter your username: ')
password = input('Enter your password: ')

register_user(username, password)

# Close the database connection
conn.close()