import sqlite3
import hashlib
import os

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE,
                        password_hash TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256(salt + password.encode()).hexdigest()

def generate_salt():
    return os.urandom(16)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    salt = generate_salt()
    password_hash = hash_password(password, salt)
    
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash.hex() + '.' + salt.hex()))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} is already taken.")
    
    conn.close()

def main():
    create_table()
    while True:
        username = input("Enter a username: ")
        password = input("Enter a password: ")
        
        register_user(username, password)
        
        another = input("Register another user? (yes/no): ").lower()
        if another != 'yes':
            break

if __name__ == "__main__":
    main()