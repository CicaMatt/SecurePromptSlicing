import sqlite3
import hashlib

def create_database():
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
    return hashlib.sha256(password.encode()).hexdigest()

def add_user_to_database(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        password_hash = hash_password(password)
        cursor.execute(
            'INSERT INTO users (username, password_hash) VALUES (?, ?)',
            (username, password_hash)
        )
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    
    add_user_to_database(username, password)
    print("User registered successfully.")

if __name__ == "__main__":
    main()