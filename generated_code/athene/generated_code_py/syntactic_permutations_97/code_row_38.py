import sqlite3
from hashlib import sha256

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash TEXT, first_name TEXT, last_name TEXT, email TEXT)''')

    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        conn.close()
        return "Username already exists"

    password_hash = sha256(password.encode()).hexdigest()
    c.execute("INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", 
              (username, password_hash, first_name, last_name, email))
    
    conn.commit()
    conn.close()
    return "Registration succeeded"

# Example usage
username = 'johndoe'
password = 'securepassword123'
first_name = 'John'
last_name = 'Doe'
email = 'john.doe@example.com'

print(register_user(username, password, first_name, last_name, email))