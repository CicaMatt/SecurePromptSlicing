import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        hashed_password TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        hashed_password = hash_password(password)
        salt = "salt_value"  # In a real application, generate a unique salt for each user
        stored_data = f"{username}{hashed_password}"
        
        cursor.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", 
                       (username, stored_data))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

create_database()
register_user('testuser', 'password123')