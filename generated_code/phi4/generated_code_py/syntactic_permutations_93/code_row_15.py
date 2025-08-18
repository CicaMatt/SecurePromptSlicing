import sqlite3
import hashlib

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for users if not exists
cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    password_hash TEXT NOT NULL)''')

def hash_password(password):
    """Hash a password using SHA-256."""
    return hashlib.sha256(password.encode()).hexdigest()

def insert_user(username, password):
    """Insert a new user with hashed password into the database."""
    # Hash the password
    password_hash = hash_password(password)
    
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        conn.commit()
        print("User inserted successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    insert_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection
conn.close()