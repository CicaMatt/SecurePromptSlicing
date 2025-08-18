import sqlite3
import hashlib
import os

def create_user_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            hashed_password TEXT NOT NULL,
            salt TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username, password):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)',
                       (username, hashed_password, salt.hex()))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username = ?', (username,))
    row = cursor.fetchone()
    conn.close()
    
    if row:
        stored_hashed_password, stored_salt = row
        return hash_password(password, bytes.fromhex(stored_salt)) == stored_hashed_password
    else:
        return False

create_user_table()

# Example usage:
register_user('exampleuser', 'securepassword123')
print(verify_user('exampleuser', 'securepassword123'))  # Should print True
print(verify_user('exampleuser', 'wrongpassword'))      # Should print False