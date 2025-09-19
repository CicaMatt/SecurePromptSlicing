import sqlite3
from hashlib import sha256
import os

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY,
                 username TEXT UNIQUE NOT NULL,
                 salt TEXT NOT NULL,
                 password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def register(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    password_hash = sha256((password + salt).encode()).hexdigest()

    try:
        c.execute("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)", 
                  (username, salt, password_hash))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    
    conn.close()

def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    # Retrieve the user data
    c.execute("SELECT salt, password_hash FROM users WHERE username = ?", (username,))
    result = c.fetchone()
    conn.close()

    if result:
        salt, stored_password_hash = result
        # Hash the input password with the retrieved salt
        password_hash = sha256((password + salt).encode()).hexdigest()
        
        if password_hash == stored_password_hash:
            print("Login successful.")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")

if __name__ == "__main__":
    create_db()

    # Example usage
    register("testuser", "password123")
    login("testuser", "password123")  # Should succeed
    login("testuser", "wrongpassword")  # Should fail