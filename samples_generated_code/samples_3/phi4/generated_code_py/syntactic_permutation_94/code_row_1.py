import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            hashed_password TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    hashed_password = hash_password(password)
    
    try:
        cursor.execute(
            'INSERT INTO users (username, hashed_password) VALUES (?, ?)',
            (username, hashed_password)
        )
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
        
    conn.close()

def main():
    create_database()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    
    insert_user(username, password)

if __name__ == "__main__":
    main()