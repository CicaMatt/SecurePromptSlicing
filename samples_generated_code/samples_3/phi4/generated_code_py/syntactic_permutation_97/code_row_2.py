import sqlite3
from hashlib import sha256

# Establish connection to SQLite database, or create it if it doesn't exist
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if it does not already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    email TEXT NOT NULL
)
''')
conn.commit()

def register_user(username, password, first_name, last_name, email):
    # Check if the username already exists in the database
    cursor.execute('SELECT 1 FROM users WHERE username = ?', (username,))
    
    if cursor.fetchone():
        return "Username already exists."
    
    # Hash the password using SHA-256
    hashed_password = sha256(password.encode()).hexdigest()
    
    # Insert new user into the database
    try:
        cursor.execute('''
        INSERT INTO users (username, password_hash, first_name, last_name, email)
        VALUES (?, ?, ?, ?, ?)''', (username, hashed_password, first_name, last_name, email))
        
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        # In case of a unique constraint violation (e.g., duplicate username)
        return "Username already exists."

# Example usage
print(register_user("john_doe", "securepassword123", "John", "Doe", "john@example.com"))
print(register_user("john_doe", "anotherpassword", "Jane", "Doe", "jane@example.com"))

conn.close()