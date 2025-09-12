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
    # Hash the password using SHA-256
    return sha256(password.encode()).hexdigest()

def register_user(username, password):
    # Hash the password
    hashed_password = hash_password(password)

    # Insert user into the database
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', 
                       (username, hashed_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    # Get username and password from the user
    username = input("Enter username: ")
    password = input("Enter password: ")

    # Register the user
    register_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection to the database
conn.close()