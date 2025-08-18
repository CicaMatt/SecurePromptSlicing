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

def insert_user(username, password):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    try:
        password_hash = hash_password(password)
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        connection.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        connection.close()

def main():
    create_database()
    
    username = input("Enter username: ")
    if not username.strip():
        print("Username cannot be empty.")
        return
    
    password = input("Enter password: ")
    if not password.strip():
        print("Password cannot be empty.")
        return
    
    insert_user(username, password)
    print("User registered successfully.")

if __name__ == "__main__":
    main()