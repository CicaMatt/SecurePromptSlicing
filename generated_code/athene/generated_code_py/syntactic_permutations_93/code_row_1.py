import sqlite3
import hashlib

def create_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT)''')
    
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    
    c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
    conn.commit()
    conn.close()

# Example usage
create_user('john_doe', 's3cureP4ssw0rd')