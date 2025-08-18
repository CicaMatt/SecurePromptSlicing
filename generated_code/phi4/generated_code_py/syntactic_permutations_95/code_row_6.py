import sqlite3
from hashlib import sha256
import os

def create_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT UNIQUE NOT NULL,
                 password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    salt = os.urandom(16)
    password_hash = sha256(salt + password.encode()).hexdigest()
    return password_hash, salt

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    password_hash, salt = hash_password(password)
    try:
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                  (username, password_hash + salt.hex()))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Registration failed: {e}")
        return False
    finally:
        conn.close()
    
    return True

def verify_password(username, input_password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT password_hash FROM users WHERE username=?", (username,))
    result = c.fetchone()
    
    if not result:
        print("User not found.")
        return False
    
    stored_password_hash_with_salt = result[0]
    salt = bytes.fromhex(stored_password_hash_with_salt[-32:])
    stored_password_hash = stored_password_hash_with_salt[:-32]
    
    input_password_hash, _ = hash_password(input_password)
    if sha256(salt + input_password.encode()).hexdigest() == stored_password_hash:
        print("Login successful.")
        return True
    else:
        print("Invalid username or password.")
        return False

if __name__ == "__main__":
    create_db()
    
    # Example usage:
    username = "test_user"
    password = "securepassword123"

    if register_user(username, password):
        verify_password(username, password)