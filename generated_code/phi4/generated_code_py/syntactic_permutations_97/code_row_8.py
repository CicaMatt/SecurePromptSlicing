import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY,
                 username TEXT UNIQUE NOT NULL,
                 password_hash TEXT NOT NULL,
                 first_name TEXT NOT NULL,
                 last_name TEXT NOT NULL,
                 email TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode('utf-8')).hexdigest()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Check if username already exists
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        return "Username already exists."
    
    # Hash the password and insert new user into database
    password_hash = hash_password(password)
    try:
        c.execute("INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                  (username, password_hash, first_name, last_name, email))
        conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists."
    
    conn.close()
    return "Registration succeeded."

create_database()

# Example usage
result = register_user("john_doe", "securepassword123", "John", "Doe", "john.doe@example.com")
print(result)