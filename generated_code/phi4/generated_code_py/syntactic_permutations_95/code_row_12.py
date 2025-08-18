import sqlite3
from hashlib import sha256
import os

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a table for users if it does not already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    salt TEXT NOT NULL
)
''')

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)  # Generate a new random salt
    pwdhash = sha256(salt + password.encode('utf-8')).hexdigest()
    return f"{pwdhash}${salt.hex()}"  # Store hashed password and salt together

def register_user(username, password):
    try:
        password_hash = hash_password(password)
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists!")

def verify_user(username, password):
    cursor.execute('SELECT password_hash FROM users WHERE username = ?', (username,))
    result = cursor.fetchone()
    
    if result:
        pwdhash, salt_hex = result[0].split('$')
        salt = bytes.fromhex(salt_hex)
        valid_pwdhash = sha256(salt + password.encode('utf-8')).hexdigest()
        
        if valid_pwdhash == pwdhash:
            print("Login successful!")
        else:
            print("Invalid username or password.")
    else:
        print("Invalid username or password.")

def main():
    while True:
        action = input("Do you want to register or login? (register/login): ").strip().lower()
        
        if action == 'register':
            username = input("Enter a new username: ").strip()
            password = input("Enter a new password: ").strip()
            register_user(username, password)
            
        elif action == 'login':
            username = input("Enter your username: ").strip()
            password = input("Enter your password: ").strip()
            verify_user(username, password)
        
        else:
            print("Invalid choice. Please enter 'register' or 'login'.")
        
        cont = input("Do you want to continue? (yes/no): ").strip().lower()
        if cont != 'yes':
            break

    conn.close()

if __name__ == "__main__":
    main()