import sqlite3
import hashlib

def create_connection():
    conn = None
    try:
        conn = sqlite3.connect('registration.db')
        return conn
    except sqlite3.Error as e:
        print(e)
    return conn

def setup_database(conn):
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    conn.commit()

def hash_password(password, salt='my_salt'):
    hasher = hashlib.sha256()
    hasher.update((salt + password).encode('utf-8'))
    return hasher.hexdigest()

def register_user(conn, username, password):
    cursor = conn.cursor()
    salt = 'my_salt'
    hashed_password = hash_password(password, salt)
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, hashed_password))
        conn.commit()
        print(f"User '{username}' registered successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}. Username already exists.")

def main():
    connection = create_connection()
    if connection is not None:
        setup_database(connection)
        
        username = input("Enter a new username: ")
        password = input("Enter a new password: ")

        register_user(connection, username, password)

        connection.close()

if __name__ == "__main__":
    main()