import sqlite3
from hashlib import pbkdf2_hmac

# Create a SQLite database and connect to it
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for storing user credentials
cursor.execute('''CREATE TABLE IF NOT EXISTS users
             (id INTEGER PRIMARY KEY, username TEXT, hashed_password TEXT)''')

def hash_password(password):
    salt = b'salt'
    return pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    hashed_password = hash_password(password)
    cursor.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", 
                   (username, hashed_password.hex()))
    conn.commit()

# Example usage
register_user('exampleuser', 'examplepassword')

# Close the connection to the database
conn.close()