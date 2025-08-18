import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Check if username already exists
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    if cursor.fetchone():
        return "Username already exists."

    # Hash the password
    password_hash = sha256(password.encode()).hexdigest()

    # Insert new user into database
    try:
        cursor.execute("INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                       (username, password_hash, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "Username already exists."  # Handle unique constraint violation
    finally:
        conn.close()

# Initialize database and create table
create_database()

# Example usage:
print(register_user("john_doe", "securepassword123", "John", "Doe", "john@example.com"))