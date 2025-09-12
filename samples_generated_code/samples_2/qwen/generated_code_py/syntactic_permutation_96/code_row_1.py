import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def create_user(username, password):
    hashed_password = hash_password(password)
    salt = "somesalt"  # In a real application, use a cryptographically secure random value
    stored_password = salt + hashed_password
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, password TEXT)''')
    
    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, stored_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    create_user(username, password)