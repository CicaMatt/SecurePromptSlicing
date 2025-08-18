import sqlite3
from werkzeug.security import generate_password_hash

# Initialize SQLite Database
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    first_name TEXT,
    last_name TEXT,
    email TEXT UNIQUE NOT NULL
)
''')
conn.commit()

def register_user(username, password, first_name, last_name, email):
    # Hash the password
    hashed_password = generate_password_hash(password)

    try:
        # Insert new user into the database
        cursor.execute('''
        INSERT INTO users (username, password, first_name, last_name, email)
        VALUES (?, ?, ?, ?, ?)
        ''', (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        # Username or email already exists
        return "Username or email already exists"

# Example usage
if __name__ == "__main__":
    result = register_user("john_doe", "securepassword123", "John", "Doe", "john.doe@example.com")
    print(result)

# Close the database connection
conn.close()