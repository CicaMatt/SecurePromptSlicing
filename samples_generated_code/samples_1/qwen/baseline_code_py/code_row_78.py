import hashlib
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def insert_user(username, password):
    salt = b'somesalt'  # In a real application, this should be randomly generated for each user
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password BLOB)''')
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    insert_user(username, password)