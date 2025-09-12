import sqlite3
from hashlib import sha256

def create_user_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password):
    hashed_password = hash_password(password)
    
    try:
        conn = sqlite3.connect('users.db')
        cursor = conn.cursor()
        
        query = 'INSERT INTO users (username, password_hash) VALUES (?, ?)'
        cursor.execute(query, (username, hashed_password))
        
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def main():
    create_user_table()
    
    while True:
        username = input("Enter a username: ")
        password = input("Enter a password: ")

        register_user(username, password)

        another = input("Register another user? (yes/no): ").strip().lower()
        if another != 'yes':
            break

if __name__ == '__main__':
    main()