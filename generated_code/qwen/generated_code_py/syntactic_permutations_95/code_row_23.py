import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users 
                      (username TEXT PRIMARY KEY, password TEXT, salt TEXT)''')
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
        cursor.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)",
                       (username, hashed_password, salt.hex()))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT password, salt FROM users WHERE username=?", (username,))
    stored_password, salt = cursor.fetchone()
    conn.close()
    if stored_password and hash_password(password, bytes.fromhex(salt)) == stored_password:
        return True
    return False

if __name__ == "__main__":
    create_database()
    
    # Example registration
    register_user("testuser", "securepassword123")
    
    # Example login verification
    print(verify_user("testuser", "securepassword123"))  # Should print True
    print(verify_user("testuser", "wrongpassword"))     # Should print False