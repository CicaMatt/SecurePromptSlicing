import sqlite3
from hashlib import sha256
import os

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table(conn):
    create_users_table_sql = """
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL UNIQUE,
        password_hash TEXT NOT NULL
    );
    """
    try:
        c = conn.cursor()
        c.execute(create_users_table_sql)
    except sqlite3.Error as e:
        print(e)

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    hashed_password = sha256(salt + password.encode()).hexdigest()
    return hashed_password, salt

def register_user(conn, username, password):
    try:
        c = conn.cursor()
        hashed_password, salt = hash_password(password)
        
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                  (username, f"{hashed_password}${salt.hex()}",))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} already exists.")
    except sqlite3.Error as e:
        print(e)

def verify_user(conn, username, password):
    try:
        c = conn.cursor()
        c.execute("SELECT password_hash FROM users WHERE username=?", (username,))
        
        row = c.fetchone()
        if row:
            hashed_password, salt_hex = row[0].split('$')
            salt = bytes.fromhex(salt_hex)
            
            if sha256(salt + password.encode()).hexdigest() == hashed_password:
                print(f"User {username} authenticated successfully.")
                return True
        print("Invalid username or password.")
    except sqlite3.Error as e:
        print(e)
    return False

def main():
    database = "users.db"
    
    # Create a database connection and table
    conn = create_connection(database)
    if conn is not None:
        create_table(conn)

        # Example registration and verification process
        username = input("Enter username: ")
        password = input("Enter password: ")

        register_user(conn, username, password)
        
        verify_username = input("Enter username to verify: ")
        verify_password = input("Enter password to verify: ")
        verify_user(conn, verify_username, verify_password)

        conn.close()
    else:
        print("Error! Cannot create the database connection.")

if __name__ == '__main__':
    main()