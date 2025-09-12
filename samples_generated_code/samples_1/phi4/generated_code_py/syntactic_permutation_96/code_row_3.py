import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create users table if it does not exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL
)
''')

def hash_password(password, salt):
    return sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    # Define a constant salt for hashing passwords
    SALT = "my_salt_value"

    # Hash the password with salt
    hashed_password = hash_password(password, SALT)

    # Concatenate the salt and hashed password
    stored_password = f"{SALT}{hashed_password}"

    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, stored_password))
        conn.commit()
        print(f"User '{username}' registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username '{username}' already exists.")

def main():
    # Example usage
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    register_user(username, password)

if __name__ == "__main__":
    main()

# Close the database connection when done (in actual application code, consider handling this elsewhere)
conn.close()