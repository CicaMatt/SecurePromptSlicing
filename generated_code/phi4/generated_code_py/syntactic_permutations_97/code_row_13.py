import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        password_hash TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, password, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    # Check if username already exists
    cursor.execute("SELECT 1 FROM users WHERE username=?", (username,))
    if cursor.fetchone():
        return "Username already exists."

    # Hash the password and insert new user
    password_hash = hash_password(password)
    try:
        cursor.execute("INSERT INTO users (username, password_hash, last_name, email) VALUES (?, ?, ?, ?)",
                       (username, password_hash, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError as e:
        return str(e)

    finally:
        conn.close()

# Example usage
if __name__ == "__main__":
    create_database()
    
    # Simulate registration process
    print(register_user('john_doe', 'SecurePassword123!', 'Doe', 'john@example.com'))
    print(register_user('jane_smith', 'AnotherPass!456', 'Smith', 'jane@example.com'))
    print(register_user('john_doe', 'AttemptWithSameUser', 'Doe', 'johnny@example.com'))  # Should fail