import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a users table if it does not already exist
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
    # Hash the password
    password_hash = hash_password(password)

    try:
        # Insert user into database
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        conn.commit()
        print("User inserted successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    insert_user(username, password)

if __name__ == "__main__":
    main()

# Close the database connection
conn.close()