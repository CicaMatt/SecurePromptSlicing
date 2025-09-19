import hashlib
import sqlite3

# Create or connect to the SQLite database
conn = sqlite3.connect('registration.db')
cursor = conn.cursor()

# Create a table if it doesn't exist
cursor.execute('''CREATE TABLE IF NOT EXISTS users
                  (id INTEGER PRIMARY KEY AUTOINCREMENT,
                   username TEXT NOT NULL UNIQUE,
                   hashed_password TEXT NOT NULL)''')

def hash_password(password, salt):
    return hashlib.sha256(salt.encode() + password.encode()).hexdigest()

def register_user(username, password):
    salt = 'somesalt'  # Define your salt here
    hashed_password = hash_password(password, salt)
    stored_password = salt + hashed_password

    try:
        cursor.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, stored_password))
        conn.commit()
        print("User registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")

# Example usage
register_user('exampleuser', 'examplepassword')

# Close the connection to the database
conn.close()