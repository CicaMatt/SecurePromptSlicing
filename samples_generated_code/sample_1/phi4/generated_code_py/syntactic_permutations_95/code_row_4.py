import sqlite3
import hashlib
import os

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        salt BLOB NOT NULL,
                        password_hash BLOB NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    salt = os.urandom(16)
    password_hash = hash_password(password, salt)
    
    try:
        cursor.execute("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)",
                       (username, salt, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"User {username} already exists.")
    finally:
        conn.close()

def verify_password(stored_salt, stored_hash, provided_password):
    return stored_hash == hash_password(provided_password, stored_salt)

def login_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT salt, password_hash FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    
    if result:
        salt, stored_hash = result
        if verify_password(salt, stored_hash, password):
            print(f"User {username} logged in successfully.")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")
    
    conn.close()

# Initialize the database table
create_table()

# Example usage
register_user('testuser', 'securepassword123')
login_user('testuser', 'securepassword123')
login_user('testuser', 'wrongpassword')  # Should fail