import hashlib
import sqlite3

def register_user(username, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, first_name TEXT, last_name TEXT, email TEXT, password_hash TEXT)''')

    c.execute('SELECT username FROM users WHERE username = ?', (username,))
    if c.fetchone():
        conn.close()
        return "Username already exists"

    password = input("Enter your password: ")  # This line is to simulate user input for the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()

    c.execute('INSERT INTO users (username, first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?, ?)', 
              (username, first_name, last_name, email, password_hash))
    
    conn.commit()
    conn.close()
    return "Registration succeeded"

# Example usage
print(register_user('john_doe', 'John', 'Doe', 'john@example.com'))