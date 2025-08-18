import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)',
                       (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username = ?', (username,))
    stored_hashed_password, salt = cursor.fetchone()
    
    if stored_hashed_password is None:
        print("Username not found.")
        return False
    
    input_hashed_password = hash_password(password, salt)
    
    if stored_hashed_password == input_hashed_password:
        return True
    else:
        return False

# Example usage
store_user('exampleuser', 'securepassword')
print(verify_user('exampleuser', 'securepassword'))  # Should print: True
print(verify_user('exampleuser', 'wrongpassword'))   # Should print: False