import hashlib
import sqlite3

def register_user(username, password, first_name):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT, first_name TEXT)''')
    
    c.execute('SELECT username FROM users WHERE username=?', (username,))
    if c.fetchone():
        return "Username already exists"
    
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    c.execute('INSERT INTO users (username, password, first_name) VALUES (?, ?, ?)', (username, hashed_password, first_name))
    conn.commit()
    conn.close()
    return "Registration succeeded"

# Example usage:
# print(register_user('john_doe', 'securepassword123', 'John'))