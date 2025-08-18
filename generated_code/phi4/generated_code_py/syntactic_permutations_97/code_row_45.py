import sqlite3
from hashlib import sha256

# Connect to SQLite database (or create it)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table if not exists
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
    password_hash = sha256(password.encode()).hexdigest()

    # Insert new user into database
    try:
        cursor.execute('''
        INSERT INTO users (username, password_hash, first_name, last_name, email)
        VALUES (?, ?, ?, ?, ?)''', 
                      (username, password_hash, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "An error occurred. Username might already exist."

# Example usage
print(register_user('john_doe', 'securepassword123', 'John', 'Doe', 'johndoe@example.com'))
print(register_user('john_doe', 'anotherpassword', 'Johnny', 'Doey', 'johnnydoe@example.com'))

# Close the connection
conn.close()