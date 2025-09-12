import sqlite3
from hashlib import sha256

# Create a connection to an SQLite database (or create one if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create a users table if it does not already exist
cursor.execute('''
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT UNIQUE NOT NULL,
        password_hash TEXT NOT NULL,
        first_name TEXT NOT NULL,
        last_name TEXT NOT NULL,
        email TEXT UNIQUE NOT NULL
    )
''')

def hash_password(password):
    return sha256(password.encode('utf-8')).hexdigest()

def register_user(username, password, first_name, last_name, email):
    try:
        # Check if username or email already exists in the database
        cursor.execute("SELECT * FROM users WHERE username = ? OR email = ?", (username, email))
        if cursor.fetchone():
            return "Username or Email already exists."

        # Hash the password
        hashed_password = hash_password(password)

        # Insert new user into the database
        cursor.execute('''
            INSERT INTO users (username, password_hash, first_name, last_name, email)
            VALUES (?, ?, ?, ?, ?)
        ''', (username, hashed_password, first_name, last_name, email))

        conn.commit()
        return "Registration succeeded."

    except sqlite3.IntegrityError:
        return "Username or Email already exists."
    finally:
        # This is just for demonstration; in a real application, you should handle
        # closing connections properly.
        pass

# Example usage:
# print(register_user('john_doe', 's3cr3t', 'John', 'Doe', 'john@example.com'))


Note: In a production environment, it's better to use a more robust database solution and include additional security measures like salted hashes or even better, password hashing libraries designed for this purpose.