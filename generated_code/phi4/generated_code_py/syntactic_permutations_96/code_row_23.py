import sqlite3
from hashlib import sha256

def hash_password(password: str) -> str:
    return sha256(password.encode('utf-8')).hexdigest()

def register_user(username: str, password: str):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            hashed_password TEXT NOT NULL
        )
    ''')

    # Hash the password
    hashed_pw = hash_password(password)
    
    try:
        # Insert new user into the database
        cursor.execute('INSERT INTO users (username, hashed_password) VALUES (?, ?)', 
                       (username, hashed_pw))
        conn.commit()
        print(f"User '{username}' registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    
    conn.close()

# Example usage
if __name__ == "__main__":
    user_input_username = input("Enter username: ")
    user_input_password = input("Enter password: ")

    register_user(user_input_username, user_input_password)