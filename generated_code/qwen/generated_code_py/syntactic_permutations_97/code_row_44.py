import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
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
    
    # Check if the username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    user_exists = cursor.fetchone()
    
    if user_exists:
        conn.close()
        return "Username already exists."
    
    # Hash the password
    hashed_password = hash_password(password)
    
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