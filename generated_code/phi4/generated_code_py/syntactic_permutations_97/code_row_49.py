import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it does not already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    email TEXT NOT NULL,
    password_hash TEXT NOT NULL
)
''')
conn.commit()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, first_name, last_name, email, password):
    # Check if the username already exists in the database
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    if cursor.fetchone():
        return "Username already exists."

    # Hash the password
    hashed_password = hash_password(password)

    # Insert new user into the database
    try:
        cursor.execute('''
        INSERT INTO users (username, first_name, last_name, email, password_hash)
        VALUES (?, ?, ?, ?, ?)''', 
        (username, first_name, last_name, email, hashed_password))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "An error occurred. Please try again."

# Example usage
print(register_user('john_doe', 'John', 'Doe', 'john@example.com', 'password123'))
print(register_user('john_doe', 'Jane', 'Doe', 'jane@example.com', 'password456'))

# Close the connection to the database
conn.close()