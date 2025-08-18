import sqlite3
from hashlib import sha256
import os

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL,
                        salt TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return sha256((password + salt).encode('utf-8')).hexdigest()

def register(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Generate a random salt
    salt = os.urandom(16).hex()
    hashed_password = hash_password(password, salt)
    
    try:
        cursor.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)",
                       (username, hashed_password, salt))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Registration failed: {e}")
    
    conn.close()

def verify_login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT password_hash, salt FROM users WHERE username=?", (username,))
    row = cursor.fetchone()
    conn.close()
    
    if row:
        stored_hash, salt = row
        if hash_password(password, salt) == stored_hash:
            print(f"Login successful for {username}.")
            return True
        else:
            print("Invalid password.")
            return False
    else:
        print("Username not found.")
        return False

def main():
    create_table()
    
    # Example usage
    username = input("Register - Enter username: ")
    password = input("Enter password: ")
    register(username, password)
    
    login_username = input("Login - Enter username: ")
    login_password = input("Enter password: ")
    verify_login(login_username, login_password)

if __name__ == "__main__":
    main()