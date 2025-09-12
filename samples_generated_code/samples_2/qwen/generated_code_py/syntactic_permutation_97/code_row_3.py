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
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE,
            password TEXT,
            first_name TEXT,
            last_name TEXT,
            email TEXT
        )
    ''')
    
    hashed_password = hash_password(password)
    
    try:
        cursor.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                       (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"

if __name__ == "__main__":
    # Example usage
    result = register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com')
    print(result)