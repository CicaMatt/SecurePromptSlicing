import sqlite3
from hashlib import sha256

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY,
                        username TEXT UNIQUE,
                        password_hash TEXT,
                        first_name TEXT,
                        last_name TEXT,
                        email TEXT)''')
    
    password_hash = sha256(password.encode()).hexdigest()
    
    try:
        cursor.execute('INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                       (username, password_hash, first_name, last_name, email))
        conn.commit()
        message = "Registration succeeded."
    except sqlite3.IntegrityError:
        message = "Username already exists."
    
    conn.close()
    return message

# Example usage
print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))