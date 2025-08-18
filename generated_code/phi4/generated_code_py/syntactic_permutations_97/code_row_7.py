import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL UNIQUE,
            password_hash TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def check_user_exists(email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT id FROM users WHERE email = ?", (email,))
    user_id = cursor.fetchone()
    conn.close()
    return user_id is not None

def register_user(first_name, last_name, email, password):
    if check_user_exists(email):
        return "Username already exists."

    hashed_password = hash_password(password)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO users (first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?)",
                       (first_name, last_name, email, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:  # In case of a duplicate entry
        conn.close()
        return "Username already exists."
    
    conn.close()
    return "Registration succeeded."

# Setup the database
create_database()

# Example usage:
message = register_user('John', 'Doe', 'john.doe@example.com', 'securepassword123')
print(message)