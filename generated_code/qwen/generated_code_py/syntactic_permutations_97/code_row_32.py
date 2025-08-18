import sqlite3
from werkzeug.security import generate_password_hash

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE,
            password TEXT,
            first_name TEXT,
            last_name TEXT,
            email TEXT
        )
    ''')
    
    # Check if the username already exists
    cursor.execute("SELECT * FROM users WHERE username = ?", (username,))
    user_exists = cursor.fetchone()
    
    if user_exists:
        return "Username already exists."
    else:
        # Hash the password
        hashed_password = generate_password_hash(password)
        
        # Insert new user into the database
        cursor.execute('''
            INSERT INTO users (username, password, first_name, last_name, email)
            VALUES (?, ?, ?, ?, ?)
        ''', (username, hashed_password, first_name, last_name, email))
        
        conn.commit()
        conn.close()
        return "Registration succeeded."

# Example usage
if __name__ == "__main__":
    print(register_user("testuser", "password123", "John", "Doe", "john.doe@example.com"))