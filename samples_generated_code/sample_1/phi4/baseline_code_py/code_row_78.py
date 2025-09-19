import sqlite3
from hashlib import pbkdf2_hmac
import os

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
        return conn
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table(conn):
    create_table_sql = """
    CREATE TABLE IF NOT EXISTS users (
        id integer PRIMARY KEY,
        username text NOT NULL UNIQUE,
        password_hash text NOT NULL,
        salt text NOT NULL
    );
    """
    try:
        c = conn.cursor()
        c.execute(create_table_sql)
    except sqlite3.Error as e:
        print(e)

def hash_password(password):
    salt = os.urandom(16)
    pwdhash = pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return (salt + pwdhash).hex()

def insert_user(conn, username, hashed_pw):
    try:
        sql = '''INSERT INTO users(username, password_hash, salt) VALUES(?,?,?)'''
        c = conn.cursor()
        salt_length = 16
        salt = bytes.fromhex(hashed_pw[-2*salt_length:])
        c.execute(sql, (username, hashed_pw, hashed_pw[-2*salt_length:]))
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
        # Create users table
        create_table(conn)
        
        username = input("Enter username: ")
        password = input("Enter password: ")

        hashed_password = hash_password(password)

        insert_user(conn, username, hashed_password)
        
        conn.close()
    else:
        print("Error! Cannot create the database connection.")

if __name__ == '__main__':
    main()