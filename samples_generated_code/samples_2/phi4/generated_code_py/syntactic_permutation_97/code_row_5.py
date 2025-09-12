import sqlite3
from hashlib import sha256

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except sqlite3.Error as e:
        print(e)
    return conn

def register_user(conn, username, password, first_name, last_name, email):
    cursor = conn.cursor()
    
    # Check if username already exists
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    existing_user = cursor.fetchone()

    if existing_user:
        return "Username already exists."

    # Hash the password
    hashed_password = sha256(password.encode()).hexdigest()

    # Insert new user into database
    try:
        cursor.execute(
            "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
            (username, hashed_password, first_name, last_name, email)
        )
        conn.commit()
        return "Registration succeeded."
    except sqlite3.Error as e:
        print(e)
        return "An error occurred during registration."

def main():
    database = "users.db"

    # Create a new SQLite database and table if not exists
    conn = create_connection(database)

    with conn:
        cursor = conn.cursor()
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL,
                first_name TEXT NOT NULL,
                last_name TEXT NOT NULL,
                email TEXT NOT NULL
            )
        """)

    # Example registration process
    result = register_user(conn, "john_doe", "securepassword123", "John", "Doe", "john@example.com")
    print(result)

if __name__ == "__main__":
    main()