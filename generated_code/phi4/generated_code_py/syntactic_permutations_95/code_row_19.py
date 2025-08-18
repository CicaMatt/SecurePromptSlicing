import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT UNIQUE NOT NULL,
                 salt TEXT NOT NULL,
                 password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode('utf-8')).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    salt = os.urandom(16).hex()
    password_hash = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, salt, password_hash) VALUES (?, ?, ?)",
                  (username, salt, password_hash))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Try a different username.")
    
    conn.close()

def main():
    create_database()
    while True:
        username = input("Enter username: ")
        password = input("Enter password: ")
        
        register_user(username, password)
        
        another = input("Register another user? (yes/no): ").lower()
        if another != 'yes':
            break

if __name__ == "__main__":
    main()