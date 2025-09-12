import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def create_user(username, password):
    hashed_password = hash_password(password)
    salt = "somesalt"  # In practice, use a secure random salt for each user
    combined_password = salt + hashed_password
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, combined_password))
    conn.commit()
    conn.close()

# Example usage
create_user('exampleuser', 'examplepassword')