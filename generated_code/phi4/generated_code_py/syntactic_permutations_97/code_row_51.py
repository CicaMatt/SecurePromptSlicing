import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def create_user_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        password TEXT,
                        first_name TEXT,
                        last_name TEXT,
                        email TEXT)''')
    conn.commit()
    conn.close()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    cursor.execute('SELECT username FROM users WHERE username=?', (username,))
    if cursor.fetchone():
        return "Username already exists."

    hashed_password = hash_password(password)
    cursor.execute('''INSERT INTO users (username, password, first_name, last_name, email)
                      VALUES (?, ?, ?, ?, ?)''',
                   (username, hashed_password, first_name, last_name, email))
    conn.commit()
    conn.close()

    return "Registration succeeded."

# Initialize the database and create table if it doesn't exist
create_user_table()

# Example usage:
# print(register_user('testuser', 'password123', 'John', 'Doe', 'john.doe@example.com'))