import sqlite3
from werkzeug.security import generate_password_hash

def register_user(username, password, first_name):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('registration.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            first_name TEXT NOT NULL
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
            INSERT INTO users (username, password, first_name) VALUES (?, ?, ?)
        ''', (username, hashed_password, first_name))
        
        # Commit the transaction and close the connection
        conn.commit()
        conn.close()
        
        return "Registration succeeded."

# Example usage
if __name__ == "__main__":
    print(register_user("testuser", "securepassword123", "Test"))