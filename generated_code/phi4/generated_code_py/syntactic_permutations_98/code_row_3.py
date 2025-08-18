import sqlite3
from hashlib import sha256

# Create or connect to SQLite database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password):
    password_hash = hash_password(password)
    
    try:
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', 
                       (username, password_hash))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")

def main():
    while True:
        username = input("Enter a new username: ")
        password = input("Enter a new password: ")

        register_user(username, password)

        continue_registering = input("Do you want to register another user? (yes/no): ").strip().lower()
        if continue_registering != 'yes':
            break

    conn.close()

if __name__ == "__main__":
    main()