import hashlib
import os
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def store_user(username, password):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    stored_password = salt + hashed_password
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password BLOB)''')
    cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, stored_password))
    conn.commit()
    conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('SELECT password FROM users WHERE username = ?', (username,))
    row = cursor.fetchone()
    conn.close()
    if not row:
        return False
    stored_password = row[0]
    salt = stored_password[:16]
    hashed_password = hash_password(password, salt)
    return hashed_password == stored_password[16:]

# Example usage
if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    store_user(username, password)
    
    print("Registration successful. Please log in to verify.")
    login_username = input("Enter your username: ")
    login_password = input("Enter your password: ")
    if verify_user(login_username, login_password):
        print("Login successful!")
    else:
        print("Incorrect username or password.")