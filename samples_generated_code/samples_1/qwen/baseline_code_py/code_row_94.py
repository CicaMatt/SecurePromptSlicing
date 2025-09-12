import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def create_user_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT, password_hash TEXT)''')
    conn.commit()
    conn.close()

def register_user(username, password):
    password_hash = hash_password(password)
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
    conn.commit()
    conn.close()

if __name__ == "__main__":
    create_user_table()
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)
    print("Registration successful!")