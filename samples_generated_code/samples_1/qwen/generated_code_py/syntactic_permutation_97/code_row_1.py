import sqlite3
from werkzeug.security import generate_password_hash

# Set up SQLite connection
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    email TEXT NOT NULL
)
''')
conn.commit()

def register_user(username, password, first_name, last_name, email):
    try:
        # Hash the password
        hashed_password = generate_password_hash(password)

        # Insert new user into the database
        cursor.execute('''
        INSERT INTO users (username, password, first_name, last_name, email)
        VALUES (?, ?, ?, ?, ?)
        ''', (username, hashed_password, first_name, last_name, email))
        
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        # If username already exists
        return "Username already exists"

# Example usage
if __name__ == "__main__":
    print(register_user("testuser", "password123", "John", "Doe", "john.doe@example.com"))
    print(register_user("testuser", "anotherpassword", "Jane", "Smith", "jane.smith@example.com"))

# Close the connection
conn.close()