import hashlib
import sqlite3

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if not exists
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT UNIQUE,
                    password_hash TEXT,
                    first_name TEXT,
                    last_name TEXT,
                    email TEXT)''')

    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()

    try:
        # Insert user into database
        c.execute('INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                  (username, password_hash, first_name, last_name, email))
        conn.commit()
        message = "Registration successful"
    except sqlite3.IntegrityError:
        message = "Username already exists"
    finally:
        conn.close()

    return message