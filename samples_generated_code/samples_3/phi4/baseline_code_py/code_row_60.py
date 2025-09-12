import sqlite3
from hashlib import sha256

# Initialize or connect to a SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for users if it doesn't exist
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
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    
    if cursor.fetchone() is not None:
        return "Username already exists."
    
    password_hash = hash_password(password)
    
    try:
        cursor.execute(
            'INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
            (username, password_hash, first_name, last_name, email)
        )
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "An error occurred. Please try again."

# Example usage
print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john.doe@example.com'))
print(register_user('john_doe', 'newpassword456', 'Johnny', 'Doe', 'johnd@example.com'))

conn.close()