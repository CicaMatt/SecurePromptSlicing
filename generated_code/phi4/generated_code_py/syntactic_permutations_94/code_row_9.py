import sqlite3
from hashlib import sha256

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def setup_database(conn):
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(conn, username, password):
    cursor = conn.cursor()
    hashed_password = hash_password(password)
    try:
        cursor.execute('''
            INSERT INTO users (username, password_hash) VALUES (?, ?)
        ''', (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    db_file = 'users.db'
    conn = create_connection(db_file)

    if conn is not None:
        setup_database(conn)

        username = input("Enter a username: ")
        password = input("Enter a password: ")

        register_user(conn, username, password)
        
        conn.close()
    else:
        print("Error! Cannot create the database connection.")

if __name__ == '__main__':
    main()