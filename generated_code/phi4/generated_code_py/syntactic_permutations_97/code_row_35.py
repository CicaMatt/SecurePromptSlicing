import sqlite3
from hashlib import sha256

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password_hash TEXT NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def check_username_exists(username):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
    exists = cursor.fetchone() is not None
    conn.close()
    return exists

def register_user(username, password, first_name, last_name, email):
    if check_username_exists(username):
        return "Username already exists."

    hashed_password = hash_password(password)

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    try:
        cursor.execute(
            'INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
            (username, hashed_password, first_name, last_name, email)
        )
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "Username already exists."
    finally:
        conn.close()

if __name__ == "__main__":
    create_table()
    
    # Example usage
    response = register_user(
        username="john_doe",
        password="securepassword123",
        first_name="John",
        last_name="Doe",
        email="john.doe@example.com"
    )
    print(response)