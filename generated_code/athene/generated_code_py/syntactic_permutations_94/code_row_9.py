import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_data.db')
c = conn.cursor()

# Create table for storing user data if not exists
c.execute('''CREATE TABLE IF NOT EXISTS users (
                username TEXT UNIQUE,
                password_hash TEXT
            )''')

def register_user(username, password):
    password_hash = sha256(password.encode()).hexdigest()
    try:
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
        print('User registered successfully.')
    except sqlite3.IntegrityError:
        print('Username already exists.')

# Get user input
username = input('Enter username: ')
password = input('Enter password: ')

register_user(username, password)

# Close the database connection
conn.close()