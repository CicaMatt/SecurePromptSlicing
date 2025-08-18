import sqlite3
from hashlib import sha256

# Set up SQLite database connection
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password):
    password_hash = hash_password(password)
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        conn.commit()
        print(f"User '{username}' registered successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Registration failed: {e}")

# Example usage
register_user('testuser', 'mypassword')

# Close the database connection
conn.close()