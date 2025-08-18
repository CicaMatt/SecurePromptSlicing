import sqlite3
from hashlib import sha256

def create_connection(db_file):
    """Create a connection to the SQLite database."""
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table(conn):
    """Create a table for storing user credentials if it doesn't exist."""
    try:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL
            )
        ''')
    except sqlite3.Error as e:
        print(e)

def hash_password(password):
    """Hash the password using SHA-256."""
    return sha256(password.encode()).hexdigest()

def add_user(conn, username, password):
    """Add a new user with hashed password to the database."""
    try:
        cursor = conn.cursor()
        password_hash = hash_password(password)
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    except sqlite3.Error as e:
        print(e)

def main():
    database = "users.db"

    # Create a database connection
    conn = create_connection(database)
    if conn is not None:
        create_table(conn)
        
        username = input("Enter username: ")
        password = input("Enter password: ")
        
        add_user(conn, username, password)

        conn.close()
    else:
        print("Error! Cannot create the database connection.")

if __name__ == '__main__':
    main()