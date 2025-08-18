import sqlite3
import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def create_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        hashed_password TEXT NOT NULL)''')

    # Hash the password
    hashed_pw = hash_password(password)

    try:
        # Insert new user into database
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', 
                       (username, hashed_pw))
        conn.commit()
        print(f"User '{username}' created successfully.")
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    
    conn.close()

# Example usage
create_user('example_user', 'securepassword123')