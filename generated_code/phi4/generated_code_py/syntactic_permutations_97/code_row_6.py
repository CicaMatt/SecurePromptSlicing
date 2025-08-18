import sqlite3
from hashlib import sha256

def create_database():
    connection = sqlite3.connect("users.db")
    cursor = connection.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL
        )
    """)
    connection.commit()
    connection.close()

def hash_password(password):
    return sha256(password.encode('utf-8')).hexdigest()

def register_user(username, password, first_name, last_name, email):
    connection = sqlite3.connect("users.db")
    cursor = connection.cursor()
    
    try:
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        if cursor.fetchone():
            return "Username already exists."
        
        password_hash = hash_password(password)
        cursor.execute("""
            INSERT INTO users (username, password_hash, first_name, last_name, email) 
            VALUES (?, ?, ?, ?, ?)
        """, (username, password_hash, first_name, last_name, email))
        
        connection.commit()
        return "Registration succeeded."
    
    except sqlite3.IntegrityError:
        return "Username already exists."
    
    finally:
        connection.close()

# Initialize database
create_database()

# Example usage
result = register_user("john_doe", "securepassword123", "John", "Doe", "john.doe@example.com")
print(result)