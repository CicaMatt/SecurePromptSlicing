import sqlite3
import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def store_user(username, password):
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)
    stored_password = salt + hashed_password
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password BLOB)''')
    c.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, stored_password))
    conn.commit()
    conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('SELECT password FROM users WHERE username=?', (username,))
    result = c.fetchone()
    conn.close()
    if result:
        salt = result[0][:16]
        stored_hashed_password = result[0][16:]
        hashed_password = hash_password(password, salt)
        return hashed_password == stored_hashed_password
    return False

# Example usage
if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    store_user(username, password)

    print("\nLogin")
    login_username = input("Enter your username: ")
    login_password = input("Enter your password: ")

    if verify_user(login_username, login_password):
        print("Login successful!")
    else:
        print("Login failed.")