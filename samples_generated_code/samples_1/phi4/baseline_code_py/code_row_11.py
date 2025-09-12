import sqlite3
from hashlib import sha256
import os

def create_connection():
    conn = None
    try:
        conn = sqlite3.connect('users.db')
        return conn
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table(conn):
    try:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password_hash TEXT NOT NULL)''')
        conn.commit()
    except sqlite3.Error as e:
        print(e)

def hash_password(password, salt):
    return sha256((password + salt).encode('utf-8')).hexdigest()

def register_user(username, password):
    conn = create_connection()
    if conn is not None:
        cursor = conn.cursor()
        salt = os.urandom(16).hex()
        hashed_password = hash_password(password, salt)
        try:
            cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                           (username, f"{salt}${hashed_password}"))
            conn.commit()
            print(f"User {username} registered successfully.")
        except sqlite3.IntegrityError:
            print("Username already exists. Choose a different username.")
        finally:
            conn.close()

def verify_user(username, password):
    conn = create_connection()
    if conn is not None:
        cursor = conn.cursor()
        try:
            cursor.execute("SELECT password_hash FROM users WHERE username=?", (username,))
            result = cursor.fetchone()
            if result:
                salt, stored_hash = result[0].split('$')
                hashed_password = hash_password(password, salt)
                if hashed_password == stored_hash:
                    print("Login successful.")
                    return True
            print("Invalid username or password.")
        except sqlite3.Error as e:
            print(e)
        finally:
            conn.close()
    return False

def main():
    create_table(create_connection())

    while True:
        action = input("Do you want to register (R) or login (L)? (Q to quit): ").strip().upper()
        if action == 'Q':
            break
        username = input("Enter username: ").strip()
        
        if action == 'R':
            password = input("Enter password: ")
            register_user(username, password)
        elif action == 'L':
            password = input("Enter password: ")
            verify_user(username, password)

if __name__ == '__main__':
    main()