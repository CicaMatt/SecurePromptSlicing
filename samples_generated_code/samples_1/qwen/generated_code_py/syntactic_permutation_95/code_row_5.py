import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')

    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)',
                       (username, hashed_password, salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    cursor.execute('SELECT hashed_password, salt FROM users WHERE username = ?', (username,))
    row = cursor.fetchone()
    
    if not row:
        print("Username does not exist.")
        return False

    stored_hashed_password, salt = row
    input_hashed_password = hash_password(password, salt)

    if stored_hashed_password == input_hashed_password:
        print("Login successful.")
        return True
    else:
        print("Incorrect password.")
        return False

# Example usage
if __name__ == "__main__":
    register_user('testuser', 'securepassword123')
    verify_user('testuser', 'securepassword123')
    verify_user('testuser', 'wrongpassword')