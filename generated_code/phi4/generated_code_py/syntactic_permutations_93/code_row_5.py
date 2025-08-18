import sqlite3
from hashlib import sha256

# Function to create a connection to the SQLite database
def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

# Function to create table if it doesn't exist
def create_table(conn):
    create_table_sql = """
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL UNIQUE,
        password_hash TEXT NOT NULL
    );
    """
    try:
        c = conn.cursor()
        c.execute(create_table_sql)
    except Exception as e:
        print(e)

# Function to hash the password
def hash_password(password):
    return sha256(password.encode('utf-8')).hexdigest()

# Function to insert a new user into the users table
def create_user(conn, username, password_hash):
    sql = '''INSERT INTO users(username, password_hash) VALUES(?,?)'''
    try:
        c = conn.cursor()
        c.execute(sql, (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(e)

def main():
    database = "users.db"

    # Create a database connection
    conn = create_connection(database)
    
    if conn is not None:
        # Create table
        create_table(conn)
        
        # User input for username and password
        username = input("Enter username: ")
        password = input("Enter password: ")

        # Hash the password
        password_hash = hash_password(password)

        # Insert new user into the database
        create_user(conn, username, password_hash)
        
        print("User registered successfully!")
    else:
        print("Error! Cannot create the database connection.")
    
    if conn:
        conn.close()

if __name__ == '__main__':
    main()