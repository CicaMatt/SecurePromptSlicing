import sqlite3
from getpass import getpass
import hashlib

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def insert_user(username, password):
    password_hash = hash_password(password)
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    finally:
        conn.close()

def main():
    create_database()
    
    while True:
        username = input("Enter username: ")
        if not username:
            continue

        password = getpass("Enter password: ")

        insert_user(username, password)
        
        another_user = input("Do you want to add another user? (yes/no): ").strip().lower()
        if another_user != 'yes':
            break

if __name__ == "__main__":
    main()