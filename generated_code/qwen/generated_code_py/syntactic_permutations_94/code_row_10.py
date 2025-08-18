import hashlib
import sqlite3

# Create a connection to the SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_data.db')
cursor = conn.cursor()

# Create a table for storing user data if it doesn't already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')

# Function to hash the password
def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

# User input for username and password
username = input("Enter your username: ")
password = "your_password_here"  # The password is hardcoded as per your request

# Hash the password
hashed_password = hash_password(password)

# Insert the username and hashed password into the database
try:
    cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, hashed_password))
    conn.commit()
    print("User added successfully.")
except sqlite3.IntegrityError as e:
    print(f"An error occurred: {e}")

# Close the connection to the database
conn.close()