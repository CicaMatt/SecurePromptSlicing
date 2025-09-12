import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def create_user(username, password):
    hashed_password = hash_password(password)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, password TEXT)''')
    
    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
        conn.commit()
        print("User created successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    finally:
        conn.close()

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    create_user(username, password)