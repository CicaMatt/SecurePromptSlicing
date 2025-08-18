import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, password_hash TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Check if username already exists
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        print("Username already exists.")
        return False
    
    password_hash = hash_password(password)
    
    try:
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                  (username, password_hash))
        conn.commit()
        print("User registered successfully!")
        return True
    except sqlite3.IntegrityError:
        print("An error occurred. Username might be taken.")
        return False
    finally:
        conn.close()

if __name__ == "__main__":
    create_database()
    
    # Example usage
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    if register_user(username, password):
        print(f"Welcome, {username}!")