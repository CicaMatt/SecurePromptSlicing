import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

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

    try:
        cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
        if cursor.fetchone():
            return "Username already exists"
        
        password_hash = hash_password(password)
        cursor.execute('INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                       (username, password_hash, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded"
    finally:
        conn.close()

# Example usage
print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))