import sqlite3
from hashlib import sha256

# Create a connection to the SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for storing user credentials if it doesn't already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password):
    return sha256(password.encode()).hexdigest()

# Function to add a new user
def add_user(username, password):
    password_hash = hash_password(password)
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        conn.commit()
        print("User added successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

# Main program
if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    add_user(username, password)

# Close the database connection
conn.close()