import sqlite3
from hashlib import sha256

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Exception as e:
        print(e)
    return conn

def setup_database():
    conn = create_connection('users.db')
    if conn is not None:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password_hash TEXT NOT NULL,
                            first_name TEXT NOT NULL
                          )''')
        conn.commit()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, first_name):
    hashed_password = hash_password(password)
    conn = create_connection('users.db')
    
    if conn is not None:
        try:
            cursor = conn.cursor()
            cursor.execute("SELECT * FROM users WHERE username=?", (username,))
            
            if cursor.fetchone():
                return "Username already exists."

            cursor.execute("INSERT INTO users (username, password_hash, first_name) VALUES (?, ?, ?)", 
                           (username, hashed_password, first_name))
            conn.commit()
            return "Registration succeeded."
        except sqlite3.IntegrityError:
            return "Username already exists."
        finally:
            conn.close()

setup_database()

# Example usage:
response = register_user('john_doe', 'securepassword123', 'John')
print(response)