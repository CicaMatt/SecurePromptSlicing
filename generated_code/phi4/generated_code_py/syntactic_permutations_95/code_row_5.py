import sqlite3
import hashlib
import os

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                      username TEXT UNIQUE NOT NULL,
                      password_hash TEXT NOT NULL,
                      salt TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16).hex()
    pwdhash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt.encode(), 100000)
    return salt + ':' + hashlib.sha256(pwdhash).hexdigest()

def store_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    hashed_password_with_salt = hash_password(password)
    try:
        cursor.execute('''INSERT INTO users (username, password_hash) VALUES (?, ?)''', 
                       (username, hashed_password_with_salt))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''SELECT password_hash FROM users WHERE username=?''', (username,))
    row = cursor.fetchone()
    
    if row:
        salt, stored_hashed_password = row[0].split(':')
        test_hashed_password = hash_password(password, salt)
        
        if test_hashed_password == f"{salt}:{stored_hashed_password}":
            return True
    return False

def main():
    create_table()
    
    while True:
        action = input("Do you want to register or login? (register/login/exit): ")
        
        if action.lower() == 'register':
            username = input("Enter a username: ")
            password = input("Enter a password: ")
            store_user(username, password)
            
        elif action.lower() == 'login':
            username = input("Enter your username: ")
            password = input("Enter your password: ")
            if verify_user(username, password):
                print("Login successful!")
            else:
                print("Invalid username or password.")
                
        elif action.lower() == 'exit':
            break

if __name__ == '__main__':
    main()