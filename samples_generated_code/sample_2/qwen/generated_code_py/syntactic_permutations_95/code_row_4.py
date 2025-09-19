import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       username TEXT UNIQUE NOT NULL,
                       hashed_password BLOB NOT NULL)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', (username, salt + hashed_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('SELECT hashed_password FROM users WHERE username = ?', (username,))
    stored_hashed_password = cursor.fetchone()
    
    if stored_hashed_password:
        salt = stored_hashed_password[0][:16]
        stored_hash = stored_hashed_password[0][16:]
        
        hash_to_check = hash_password(password, salt)
        if hash_to_check == stored_hash:
            print("Login successful.")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")
    
    conn.close()

# Example usage
register_user('exampleuser', 'securepassword123')
verify_user('exampleuser', 'securepassword123')