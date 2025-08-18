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
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def insert_user(conn, username, password):
    cursor = conn.cursor()
    password_hash = hash_password(password)
    try:
        cursor.execute('''
            INSERT INTO users (username, password_hash) VALUES (?, ?)
        ''', (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")

def main():
    db_file = "users.db"
    conn = create_connection(db_file)

    if conn is not None:
        setup_database(conn)
        
        username = input("Enter username: ")
        password = input("Enter password: ")

        insert_user(conn, username, password)

        conn.close()
    else:
        print("Error! cannot create the database connection.")

if __name__ == "__main__":
    main()