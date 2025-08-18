import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if it doesn't exist
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

def hash_password(password):
    return sha256(password.encode('utf-8')).hexdigest()

def register_user(username, password, first_name, last_name, email):
    cursor.execute('SELECT username FROM users WHERE username = ?', (username,))
    if cursor.fetchone():
        return "Username already exists."
    
    password_hash = hash_password(password)
    try:
        cursor.execute('''
        INSERT INTO users (username, password_hash, first_name, last_name, email) 
        VALUES (?, ?, ?, ?, ?)
        ''', (username, password_hash, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "An error occurred during registration."

# Example usage
if __name__ == "__main__":
    print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))
    # Try registering with the same username to test duplicate check
    print(register_user('john_doe', 'anotherpassword', 'Johnny', 'Doe', 'johnny@example.com'))

# Close connection when done
conn.close()