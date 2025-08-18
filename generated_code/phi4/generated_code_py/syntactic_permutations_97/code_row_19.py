import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            username TEXT UNIQUE,
            password TEXT,
            first_name TEXT,
            last_name TEXT,
            email TEXT
        )
    ''')

    # Check if username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    if cursor.fetchone():
        return "Username already exists."

    # Hash the password
    hashed_password = hash_password(password)

    # Insert new user into database
    cursor.execute('''
        INSERT INTO users (username, password, first_name, last_name, email)
        VALUES (?, ?, ?, ?, ?)
    ''', (username, hashed_password, first_name, last_name, email))

    conn.commit()
    conn.close()

    return "Registration succeeded."

# Example usage
if __name__ == "__main__":
    message = register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john.doe@example.com')
    print(message)