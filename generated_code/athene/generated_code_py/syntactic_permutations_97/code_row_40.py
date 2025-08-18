import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE,
                    password TEXT,
                    first_name TEXT,
                    last_name TEXT,
                    email TEXT
                )''')
    
    hashed_password = hash_password(password)
    
    try:
        with conn:
            c.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                      (username, hashed_password, first_name, last_name, email))
            return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"

# Example usage
print(register_user('testuser', 'password123', 'John', 'Doe', 'john@example.com'))