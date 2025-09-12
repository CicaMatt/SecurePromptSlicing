import hashlib
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    # Generate a random salt
    import os
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Insert the username and hashed password into the database
    cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)',
                   (username, hashed_password, salt))
    
    conn.commit()
    conn.close()

# Example usage
if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    insert_user(username, password)