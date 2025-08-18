import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password TEXT)''')
    
    salt = os.urandom(16)
    hashed_password_with_salt = hash_password(password, salt) + salt.hex()
    
    try:
        cursor.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", 
                       (username, hashed_password_with_salt))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT hashed_password FROM users WHERE username = ?", (username,))
    result = cursor.fetchone()
    
    if result is None:
        print("No such user.")
        return False
    
    stored_hashed_password_with_salt = result[0]
    salt = bytes.fromhex(stored_hashed_password_with_salt[-32:])
    expected_hashed_password = hash_password(password, salt)
    
    if expected_hashed_password == stored_hashed_password_with_salt[:-32]:
        print("Login successful.")
        return True
    else:
        print("Incorrect password.")
        return False

# Example usage
if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    
    action = input("Do you want to register (r) or login (l)? ").strip().lower()
    
    if action == 'r':
        register_user(username, password)
    elif action == 'l':
        verify_user(username, password)