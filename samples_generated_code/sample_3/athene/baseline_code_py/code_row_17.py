import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_data.db')
c = conn.cursor()

# Create table for storing user data
c.execute('''CREATE TABLE IF NOT EXISTS users (
                username TEXT UNIQUE,
                password_hash TEXT
            )''')

def register_user(username, password):
    # Hash the password using SHA-256
    password_hash = sha256(password.encode()).hexdigest()
    
    try:
        # Insert user into database
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

# Get username and password from user
username = input("Enter your username: ")
password = input("Enter your password: ")

register_user(username, password)

# Close the connection to the database
conn.close()