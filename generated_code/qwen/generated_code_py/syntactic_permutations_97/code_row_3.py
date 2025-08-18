import sqlite3
from werkzeug.security import generate_password_hash

# Initialize SQLite connection
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    first_name TEXT,
    last_name TEXT,
    email TEXT
);
''')
conn.commit()

def register_user(username, password, first_name, last_name, email):
    # Check if the username already exists
    cursor.execute("SELECT * FROM users WHERE username = ?", (username,))
    existing_user = cursor.fetchone()
    
    if existing_user:
        return "Username already exists."
    
    # Hash the password
    hashed_password = generate_password_hash(password)
    
    # Insert the new user into the database
    try:
        cursor.execute('''
            INSERT INTO users (username, password, first_name, last_name, email)
            VALUES (?, ?, ?, ?, ?)
        ''', (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.Error as e:
        return f"An error occurred: {e}"

# Example usage
print(register_user("testuser", "securepassword123", "John", "Doe", "john.doe@example.com"))