import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, password BLOB, salt BLOB)''')
    
    # Generate a random salt
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    
    try:
        # Insert the username and hashed password into the database
        cursor.execute("INSERT INTO users (username, password, salt) VALUES (?, ?, ?)", 
                       (username, hashed_password, salt))
        conn.commit()
        print("User inserted successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

# Example usage
if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    insert_user(username, password)