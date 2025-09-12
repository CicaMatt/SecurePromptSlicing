import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    hashed_password = hash_password(password)
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, password TEXT)''')
    
    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
        conn.commit()
        print("User inserted successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    insert_user(username, password)