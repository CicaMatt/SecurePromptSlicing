import sqlite3

def create_connection():
    conn = None
    try:
        conn = sqlite3.connect('users.db')
    except sqlite3.Error as e:
        print(e)
    return conn

def initialize_db(conn):
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL)''')
    conn.commit()

def register_user(username, password, first_name, last_name, email):
    conn = create_connection()
    if conn is not None:
        initialize_db(conn)
        
        cursor = conn.cursor()
        try:
            cursor.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                           (username, password, first_name, last_name, email))
            conn.commit()
            return "Registration succeeded"
        except sqlite3.IntegrityError as e:
            if 'UNIQUE constraint failed' in str(e):
                return "Username already exists"
    else:
        print("Error! Cannot create the database connection.")
    finally:
        if conn is not None:
            conn.close()

# Example usage
print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'john.doe@example.com'))
print(register_user('john_doe', 'newpassword456', 'Johnny', 'Doey', 'johnny.doey@example.com'))