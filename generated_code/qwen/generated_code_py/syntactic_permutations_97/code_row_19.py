import sqlite3
from werkzeug.security import generate_password_hash

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for users if it doesn't exist
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
    # Check if the username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    user_exists = cursor.fetchone()
    
    if user_exists:
        return "Username already exists."
    
    # Hash the password
    password_hash = generate_password_hash(password)
    
    # Insert new user into the database
    cursor.execute('''
    INSERT INTO users (username, password_hash, first_name, last_name, email)
    VALUES (?, ?, ?, ?, ?)
    ''', (username, password_hash, first_name, last_name, email))
    conn.commit()
    
    return "Registration succeeded."

# Example usage
if __name__ == "__main__":
    result = register_user("testuser", "securepassword123", "John", "Doe", "john.doe@example.com")
    print(result)