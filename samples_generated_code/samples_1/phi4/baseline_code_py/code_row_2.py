import sqlite3
from hashlib import sha256

def create_database():
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    connection.commit()
    connection.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def add_user_to_database(username, password):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    try:
        hashed_password = hash_password(password)
        cursor.execute('''
            INSERT INTO users (username, password_hash) VALUES (?, ?)
        ''', (username, hashed_password))
        connection.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    finally:
        connection.close()

def main():
    create_database()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    add_user_to_database(username, password)

if __name__ == "__main__":
    main()