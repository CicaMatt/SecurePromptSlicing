import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users 
                 (username TEXT PRIMARY KEY, password TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT username FROM users WHERE username = ?", (username,))
    if c.fetchone():
        return "Username already exists."
    
    hashed_password = hash_password(password)
    c.execute('''INSERT INTO users (username, password, first_name, last_name, email) 
                 VALUES (?, ?, ?, ?, ?)''', (username, hashed_password, first_name, last_name, email))
    conn.commit()
    conn.close()
    return "Registration succeeded."

create_database()

# Example usage:
response = register_user('john_doe', 'password123', 'John', 'Doe', 'john.doe@example.com')
print(response)