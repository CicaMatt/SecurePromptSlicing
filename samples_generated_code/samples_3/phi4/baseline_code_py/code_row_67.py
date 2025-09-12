import sqlite3
from hashlib import sha256

# Create/connect to SQLite database file
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

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def insert_user(username, password):
    hashed_pw = hash_password(password)
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, hashed_pw))
        conn.commit()
        print("User inserted successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    insert_user(username, password)
    
    # Close connection
    cursor.close()
    conn.close()

if __name__ == "__main__":
    main()