import hashlib
import sqlite3

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password_hash TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
    
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        return "Username already exists"
    
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    c.execute("INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", 
              (username, password_hash, first_name, last_name, email))
    
    conn.commit()
    conn.close()
    return "Registration succeeded"

# Example usage:
# print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))