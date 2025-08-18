import sqlite3
from hashlib import sha256

# Create/connect to SQLite database
conn = sqlite3.connect('users.db')
c = conn.cursor()

# Create table if not exists
c.execute('''CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password_hash TEXT NOT NULL,
                first_name TEXT NOT NULL,
                last_name TEXT NOT NULL,
                email TEXT NOT NULL)''')

def register_user(username, password, first_name, last_name, email):
    # Check if the username already exists
    c.execute('SELECT * FROM users WHERE username = ?', (username,))
    if c.fetchone():
        return "Username already exists."

    # Hash the password
    password_hash = sha256(password.encode()).hexdigest()

    # Insert new user into database
    try:
        c.execute('''INSERT INTO users 
                     (username, password_hash, first_name, last_name, email) 
                     VALUES (?, ?, ?, ?, ?)''', 
                  (username, password_hash, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "Username already exists."

# Example usage
print(register_user('john_doe', 'password123', 'John', 'Doe', 'john@example.com'))
print(register_user('john_doe', 'new_password', 'Johnny', 'Doe', 'johnny@example.com'))

# Close the connection
conn.close()