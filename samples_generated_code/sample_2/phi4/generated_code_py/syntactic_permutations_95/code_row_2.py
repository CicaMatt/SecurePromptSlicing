import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    salt = os.urandom(16)
    pwdhash = sha256(salt + password.encode()).hexdigest()
    return salt.hex() + ':' + pwdhash

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Check if username already exists
    cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
    if cursor.fetchone():
        print("Username already exists.")
        return False
    
    hashed_password = hash_password(password)
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, hashed_password))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError as e:
        print("Error:", str(e))
        return False
    finally:
        conn.close()
    
    return True

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT password_hash FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    if not result:
        print("User not found.")
        return False
    
    stored_salt_and_hash = result[0]
    salt, stored_hash = stored_salt_and_hash.split(':')
    salt_bytes = bytes.fromhex(salt)
    
    pwdhash = sha256(salt_bytes + password.encode()).hexdigest()
    if pwdhash == stored_hash:
        print("Login successful!")
        return True
    else:
        print("Invalid username or password.")
        return False

def main():
    create_database()
    
    # Example usage
    while True:
        action = input("Do you want to register (r) or login (l)? Type 'exit' to quit: ")
        
        if action.lower() == 'exit':
            break
        
        username = input("Enter your username: ")
        password = input("Enter your password: ")
        
        if action.lower() == 'r':
            register_user(username, password)
        elif action.lower() == 'l':
            verify_user(username, password)

if __name__ == "__main__":
    main()