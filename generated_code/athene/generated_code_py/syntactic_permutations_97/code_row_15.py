import hashlib
import sqlite3

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password_hash TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
    
    password_hash = hashlib.sha256(password.encode()).hexdigest()
    
    try:
        c.execute('INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)', 
                  (username, password_hash, first_name, last_name, email))
        conn.commit()
        message = "Registration succeeded"
    except sqlite3.IntegrityError:
        message = "Username already exists"
    
    conn.close()
    return message