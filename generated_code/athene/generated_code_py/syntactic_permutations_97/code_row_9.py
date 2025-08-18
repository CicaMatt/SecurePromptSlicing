import sqlite3
from hashlib import sha256

def register_user(first_name, last_name, email, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    
    hashed_password = sha256(password.encode()).hexdigest()
    
    try:
        cursor.execute('INSERT INTO users (first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?)',
                       (first_name, last_name, email, hashed_password))
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"

# Example usage
response = register_user('John', 'Doe', 'john@example.com', 'securepassword123')
print(response)