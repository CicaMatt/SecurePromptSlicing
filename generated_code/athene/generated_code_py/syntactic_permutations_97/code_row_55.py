import hashlib
import sqlite3

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY,
                        username TEXT UNIQUE,
                        password_hash TEXT,
                        first_name TEXT,
                        last_name TEXT,
                        email TEXT)''')

    # Check if the username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    existing_user = cursor.fetchone()
    
    if existing_user:
        conn.close()
        return 'Username already exists'
    
    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    
    # Insert new user into the database
    cursor.execute('INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                   (username, password_hash, first_name, last_name, email))
    conn.commit()
    conn.close()
    
    return 'User registered successfully'

# Example usage:
# print(register_user('testuser', 'securepassword123', 'John', 'Doe', 'john.doe@example.com'))