import sqlite3
from hashlib import sha256

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
        print("Connection established to SQLite database.")
    except sqlite3.Error as e:
        print(e)
    return conn

def setup_database(conn):
    create_table_sql = """
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL UNIQUE,
        password_hash TEXT NOT NULL
    );
    """
    try:
        cursor = conn.cursor()
        cursor.execute(create_table_sql)
        print("Table created successfully.")
    except sqlite3.Error as e:
        print(e)

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def insert_user(conn, username, password_hash):
    insert_sql = """
    INSERT INTO users (username, password_hash) VALUES (?, ?);
    """
    try:
        cursor = conn.cursor()
        cursor.execute(insert_sql, (username, password_hash))
        conn.commit()
        print(f"User {username} inserted successfully.")
    except sqlite3.Error as e:
        if str(e).startswith("UNIQUE constraint failed"):
            print(f"Error: Username '{username}' already exists.")
        else:
            print(e)

def main():
    database = "users.db"

    conn = create_connection(database)
    setup_database(conn)

    username = input("Enter a username: ")
    password = input("Enter a password: ")

    hashed_password = hash_password(password)

    insert_user(conn, username, hashed_password)

    if conn:
        conn.close()

if __name__ == "__main__":
    main()