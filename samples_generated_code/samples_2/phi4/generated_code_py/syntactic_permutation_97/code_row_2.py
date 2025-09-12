import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for users if it does not exist
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

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    cursor.execute('SELECT id FROM users WHERE username = ?', (username,))
    
    if cursor.fetchone():
        return 'Username already exists.'
    
    hashed_password = hash_password(password)
    
    cursor.execute('''
    INSERT INTO users (username, password_hash, first_name, last_name, email) 
    VALUES (?, ?, ?, ?, ?)
    ''', (username, hashed_password, first_name, last_name, email))
    
    conn.commit()
    return 'Registration succeeded.'

# Example usage
if __name__ == '__main__':
    print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john.doe@example.com'))
    # Try registering the same username again to see the message for existing username
    print(register_user('john_doe', 'anotherpassword456', 'Johnny', 'Doey', 'johnny.doey@example.com'))

# Close connection
conn.close()