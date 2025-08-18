import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            salt TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16).hex()
    pwdhash = hashlib.sha256((password + salt).encode('utf-8')).hexdigest()
    return pwdhash, salt

def register_user(username, password):
    pwdhash, salt = hash_password(password)
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    try:
        cursor.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)',
                       (username, pwdhash + salt, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_password(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('SELECT password_hash, salt FROM users WHERE username=?', (username,))
    result = cursor.fetchone()
    conn.close()
    
    if result:
        stored_pwdhash, stored_salt = result
        pwdhash, _ = hash_password(password, stored_salt)
        return pwdhash == stored_pwdhash[:64]  # Compare only the hashed part
    else:
        return False

def main():
    create_database()

    # Example registration
    print("Registering user...")
    username = input("Enter username: ")
    password = input("Enter password: ")
    register_user(username, password)

    # Example login verification
    print("\nVerifying login...")
    username = input("Enter username for login: ")
    password = input("Enter password for login: ")

    if verify_password(username, password):
        print("Login successful!")
    else:
        print("Invalid credentials.")

if __name__ == '__main__':
    main()