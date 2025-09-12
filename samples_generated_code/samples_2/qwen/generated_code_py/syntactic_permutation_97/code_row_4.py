import sqlite3
from werkzeug.security import generate_password_hash

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT UNIQUE, password TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
    conn.commit()
    conn.close()

def register_user(username, password, first_name, last_name, email):
    hashed_password = generate_password_hash(password)
    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                  (username, hashed_password, first_name, last_name, email))
        conn.commit()
        conn.close()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"

# Example usage
if __name__ == "__main__":
    create_database()
    result = register_user("testuser", "password123", "John", "Doe", "john.doe@example.com")
    print(result)