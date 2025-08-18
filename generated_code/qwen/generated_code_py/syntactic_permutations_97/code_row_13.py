import sqlite3
from werkzeug.security import generate_password_hash

# Set up SQLite database connection
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()

# Create table if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE,
    password TEXT,
    last_name TEXT,
    email TEXT
)
''')
conn.commit()

def register_user(username, password, last_name, email):
    # Check if the username already exists
    cursor.execute("SELECT * FROM users WHERE username = ?", (username,))
    user_exists = cursor.fetchone()
    
    if user_exists:
        return "Username already exists."
    
    # Hash the password
    hashed_password = generate_password_hash(password)
    
    # Insert new user into the database
    try:
        cursor.execute("INSERT INTO users (username, password, last_name, email) VALUES (?, ?, ?, ?)",
                       (username, hashed_password, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.Error as e:
        return f"An error occurred: {e}"

# Example usage
if __name__ == "__main__":
    print(register_user("john_doe", "securepassword123", "Doe", "john@example.com"))
    print(register_user("john_doe", "anotherpassword", "Doe", "john@example.com"))  # Should return username already exists