import hashlib
import sqlite3

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Ensure users table exists
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE,
                    password_hash TEXT,
                    first_name TEXT,
                    last_name TEXT,
                    email TEXT)''')
    
    # Check if username already exists
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        conn.close()
        return "Username already taken."
    
    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    
    # Insert new user
    c.execute("INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
              (username, password_hash, first_name, last_name, email))
    conn.commit()
    conn.close()
    
    return "Registration succeeded."

# Example usage:
# result = register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com')
# print(result)