import sqlite3
from werkzeug.security import generate_password_hash

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                      username TEXT PRIMARY KEY,
                      password TEXT,
                      first_name TEXT,
                      last_name TEXT,
                      email TEXT)''')

    hashed_password = generate_password_hash(password)

    try:
        cursor.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                       (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"

if __name__ == "__main__":
    # Example usage
    result = register_user("testuser", "password123", "John", "Doe", "john.doe@example.com")
    print(result)