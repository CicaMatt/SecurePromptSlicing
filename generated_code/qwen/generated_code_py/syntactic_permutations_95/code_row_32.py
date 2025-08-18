import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create table if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, hashed_password BLOB, salt BLOB)''')
    
    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)
    
    # Store the username and hashed password with salt in the database
    try:
        cursor.execute('INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)', 
                       (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Retrieve the stored hashed password and salt for the given username
    cursor.execute('SELECT hashed_password, salt FROM users WHERE username=?', (username,))
    result = cursor.fetchone()
    
    if result:
        stored_hashed_password, stored_salt = result
        
        # Hash the provided password with the stored salt
        provided_hashed_password = hash_password(password, stored_salt)
        
        # Verify if the provided hashed password matches the stored one
        if provided_hashed_password == stored_hashed_password:
            print("Login successful.")
        else:
            print("Incorrect password.")
    else:
        print("Username not found.")
    
    conn.close()

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)
    
    # Verify the user
    verify_username = input("Enter your username to login: ")
    verify_password = input("Enter your password to login: ")
    verify_user(verify_username, verify_password)