import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(first_name, last_name, email, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if not exists
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY,
                        first_name TEXT,
                        last_name TEXT,
                        email TEXT UNIQUE,
                        password_hash TEXT)''')
    
    hashed_password = hash_password(password)
    
    try:
        cursor.execute('INSERT INTO users (first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?)', 
                       (first_name, last_name, email, hashed_password))
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"
    finally:
        cursor.close()
        conn.close()