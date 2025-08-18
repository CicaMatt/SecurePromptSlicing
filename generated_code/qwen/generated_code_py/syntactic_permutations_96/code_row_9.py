import sqlite3
import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    pwd_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return pwd_hash

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password BLOB, salt BLOB)''')
    
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    
    try:
        c.execute('INSERT INTO users (username, password, salt) VALUES (?, ?, ?)',
                  (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

# Example usage
if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    store_user(username, password)