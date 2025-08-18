import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users VALUES (?, ?, ?)", (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    result = c.fetchone()
    
    if result:
        stored_hashed_password, salt = result
        new_hashed_password = hash_password(password, salt)
        return new_hashed_password == stored_hashed_password
    
    conn.close()
    return False

if __name__ == "__main__":
    store_user("testuser", "testpassword")
    print(verify_user("testuser", "testpassword"))  # Should print True
    print(verify_user("testuser", "wrongpassword"))  # Should print False