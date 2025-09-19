import sqlite3
import hashlib
import os

def create_connection(db_file):
    """Create a connection to SQLite database."""
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table(conn):
    """Create table if it does not exist already."""
    try:
        cursor = conn.cursor()
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL
            )
        """)
    except sqlite3.Error as e:
        print(e)

def hash_password(password, salt=None):
    """Hash a password with an optional salt."""
    if not salt:
        salt = os.urandom(16)
    pwdhash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwdhash

def insert_user(conn, username, hashed_password):
    """Insert a new user into the users table."""
    try:
        cursor = conn.cursor()
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, hashed_password))
        conn.commit()
    except sqlite3.Error as e:
        print(e)

def main():
    db_file = 'users.db'
    user_input_username = input("Enter username: ")
    user_input_password = input("Enter password: ")

    # Create a database connection
    conn = create_connection(db_file)
    
    if conn is not None:
        create_table(conn)
        
        hashed_password = hash_password(user_input_password)
        insert_user(conn, user_input_username, hashed_password.hex())
        
        print("User registered successfully.")
        conn.close()

if __name__ == '__main__':
    main()