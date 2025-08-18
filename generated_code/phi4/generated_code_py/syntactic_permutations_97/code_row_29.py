import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    username TEXT UNIQUE NOT NULL,
                    password_hash TEXT NOT NULL,
                    first_name TEXT NOT NULL,
                    last_name TEXT NOT NULL,
                    email TEXT NOT NULL
                )''')
    conn.commit()
    conn.close()

def register_user(username, password, first_name, last_name, email):
    # Hash the password
    password_hash = sha256(password.encode()).hexdigest()

    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()

        # Check if username already exists
        c.execute("SELECT * FROM users WHERE username=?", (username,))
        if c.fetchone():
            return "Username already exists."

        # Insert new user into the database
        c.execute("INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                  (username, password_hash, first_name, last_name, email))
        conn.commit()
        conn.close()
        return "Registration succeeded."

    except sqlite3.IntegrityError:
        return "Username already exists."
    except Exception as e:
        return str(e)

# Initialize the database
create_database()

# Example usage
print(register_user('john_doe', 'password123', 'John', 'Doe', 'john.doe@example.com'))