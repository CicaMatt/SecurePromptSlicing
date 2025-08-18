import sqlite3
from werkzeug.security import generate_password_hash

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for users if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    email TEXT NOT NULL
)
''')
conn.commit()

def register_user(username, password, first_name, last_name, email):
    # Check if the username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    if cursor.fetchone():
        return "Username already exists."
    
    # Hash the password
    password_hash = generate_password_hash(password)
    
    # Insert the new user into the database
    try:
        cursor.execute('INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                       (username, password_hash, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.Error as e:
        return f"An error occurred: {e}"

# Example usage
if __name__ == "__main__":
    # Test registration
    print(register_user("testuser", "password123", "John", "Doe", "john.doe@example.com"))
    print(register_user("testuser", "anotherpassword", "Jane", "Smith", "jane.smith@example.com"))

# Close the database connection
conn.close()