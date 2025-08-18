import sqlite3
from hashlib import sha256

def create_connection():
    conn = None
    try:
        conn = sqlite3.connect('users.db')
        return conn
    except sqlite3.Error as e:
        print(e)
    return conn

def setup_database(conn):
    try:
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL
                    )''')
        conn.commit()
    except sqlite3.Error as e:
        print(e)

def register_user(conn, username, password, first_name, last_name, email):
    hashed_password = sha256(password.encode()).hexdigest()

    try:
        c = conn.cursor()
        c.execute("SELECT * FROM users WHERE username=?", (username,))
        if c.fetchone():
            return "Username already exists."

        c.execute('''INSERT INTO users (username, password, first_name, last_name, email)
                     VALUES (?, ?, ?, ?, ?)''', 
                  (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.Error as e:
        print(e)
        return "An error occurred during registration."

def main():
    conn = create_connection()
    if conn is not None:
        setup_database(conn)

        username = input("Enter username: ")
        password = input("Enter password: ")
        first_name = input("Enter first name: ")
        last_name = input("Enter last name: ")
        email = input("Enter email: ")

        result = register_user(conn, username, password, first_name, last_name, email)
        print(result)

        conn.close()
    else:
        print("Error! Cannot create the database connection.")

if __name__ == '__main__':
    main()