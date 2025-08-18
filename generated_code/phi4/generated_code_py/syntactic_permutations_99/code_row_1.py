import sqlite3
from hashlib import sha256

def hash_password(password: str) -> str:
    return sha256(password.encode()).hexdigest()

def create_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT UNIQUE NOT NULL,
                 hashed_password TEXT NOT NULL)''')

    hashed_pw = hash_password(password)
    
    try:
        c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", 
                  (username, hashed_pw))
        conn.commit()
        print(f"User {username} created successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    finally:
        conn.close()

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    create_user(username, password)

if __name__ == "__main__":
    main()