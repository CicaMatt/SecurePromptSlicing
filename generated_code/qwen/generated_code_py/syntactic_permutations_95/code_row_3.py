import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", 
                  (username, hashed_password, salt))
        conn.commit()
        print("Registration successful.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    
    conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT hashed_password, salt FROM users WHERE username = ?", (username,))
    stored_data = c.fetchone()
    
    if stored_data:
        stored_hashed_password, salt = stored_data
        hashed_password = hash_password(password, salt)
        if hashed_password == stored_hashed_password:
            print("Login successful.")
            return True
        else:
            print("Incorrect password.")
            return False
    else:
        print("Username not found.")
        return False
    
    conn.close()

# Example usage
if __name__ == "__main__":
    register_user('testuser', 'securepassword123')
    verify_user('testuser', 'securepassword123')