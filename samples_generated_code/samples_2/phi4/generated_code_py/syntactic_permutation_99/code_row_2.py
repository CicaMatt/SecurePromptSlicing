import sqlite3
from hashlib import sha256

# Create or connect to a SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    password_hash TEXT
)
''')

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def insert_user(username, password):
    password_hash = hash_password(password)
    cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
    conn.commit()
    print(f"User {username} added to the database.")

# Example usage
if __name__ == "__main__":
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    try:
        insert_user(username, password)
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()