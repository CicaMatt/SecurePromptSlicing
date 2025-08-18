import sqlite3
from hashlib import sha256

# Create or connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT,
    first_name TEXT,
    last_name TEXT,
    email TEXT
)
''')

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    # Check if the username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    if cursor.fetchone():
        return "Username already exists."

    # Hash the password
    hashed_password = hash_password(password)

    # Insert new user into database
    try:
        cursor.execute('''
            INSERT INTO users (username, password_hash, first_name, last_name, email)
            VALUES (?, ?, ?, ?, ?)
        ''', (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration successful."
    except sqlite3.Error as e:
        return f"An error occurred: {e}"

# Example usage
response = register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john.doe@example.com')
print(response)

conn.close()