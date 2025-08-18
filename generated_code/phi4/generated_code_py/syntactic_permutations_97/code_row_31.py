import sqlite3
from hashlib import sha256

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
        password TEXT NOT NULL,
        first_name TEXT NOT NULL,
        last_name TEXT NOT NULL,
        email TEXT NOT NULL
    );
    """
    try:
        c = conn.cursor()
        c.execute(create_users_table_sql)
    except sqlite3.Error as e:
        print(e)

def register_user(conn, user):
    username_exists_sql = "SELECT 1 FROM users WHERE username=?"
    insert_user_sql = """
    INSERT INTO users (username, password, first_name, last_name, email)
    VALUES (?, ?, ?, ?, ?)
    """
    
    cur = conn.cursor()
    # Check if the username already exists
    cur.execute(username_exists_sql, (user['username'],))
    if cur.fetchone():
        return "Username already exists. Please choose a different one."

    hashed_password = sha256(user['password'].encode()).hexdigest()

    try:
        cur.execute(insert_user_sql, (
            user['username'],
            hashed_password,
            user['first_name'],
            user['last_name'],
            user['email']
        ))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.Error as e:
        print(e)
        return "An error occurred during registration."

def main():
    database = "registration.db"

    # Create a database connection
    conn = create_connection(database)

    if conn is not None:
        create_table(conn)

        user_info = {
            'username': input("Enter username: "),
            'password': input("Enter password: "),
            'first_name': input("Enter first name: "),
            'last_name': input("Enter last name: "),
            'email': input("Enter email: ")
        }

        message = register_user(conn, user_info)
        print(message)

        conn.close()
    else:
        print("Error! Cannot create the database connection.")

if __name__ == '__main__':
    main()