import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if not exists)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password: str) -> str:
    return sha256(password.encode()).hexdigest()

def add_user(username: str, password: str):
    hashed_password = hash_password(password)
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    add_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection
conn.close()