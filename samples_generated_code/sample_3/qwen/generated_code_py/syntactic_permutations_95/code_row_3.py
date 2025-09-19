import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password TEXT)''')
    
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt) + salt.hex()
    
    try:
        cursor.execute('INSERT INTO users VALUES (?, ?)', (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('SELECT hashed_password FROM users WHERE username = ?', (username,))
    row = cursor.fetchone()
    
    if row:
        stored_hashed_password = row[0]
        salt = bytes.fromhex(stored_hashed_password[-32:])
        expected_hashed_password = hash_password(password, salt)
        return expected_hashed_password + salt.hex() == stored_hashed_password
    else:
        return False

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    
    store_user(username, password)
    
    print("\nVerification process:")
    test_username = input("Enter your username for login: ")
    test_password = input("Enter your password for login: ")
    
    if verify_user(test_username, test_password):
        print("Login successful!")
    else:
        print("Invalid credentials.")