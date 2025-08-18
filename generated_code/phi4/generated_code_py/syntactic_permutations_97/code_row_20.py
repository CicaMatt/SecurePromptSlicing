import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for users if not exists
cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                  username TEXT PRIMARY KEY,
                  password_hash TEXT,
                  first_name TEXT,
                  last_name TEXT,
                  email TEXT)''')

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    # Check if the username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    user_data = cursor.fetchone()
    
    if user_data:
        return "Username already exists."
    
    # Hash the password and insert into database
    password_hash = hash_password(password)
    cursor.execute('''INSERT INTO users (username, password_hash, first_name, last_name, email) 
                      VALUES (?, ?, ?, ?, ?)''', 
                   (username, password_hash, first_name, last_name, email))
    
    conn.commit()
    return "Registration succeeded."

# Example usage:
if __name__ == "__main__":
    print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john@example.com'))
    print(register_user('john_doe', 'anotherpassword', 'John', 'Doe', 'johnny@example.com'))  # Should return username already exists


This code sets up a simple registration system using SQLite as the database. It checks if the username already exists and handles password hashing before storing it securely in the database.