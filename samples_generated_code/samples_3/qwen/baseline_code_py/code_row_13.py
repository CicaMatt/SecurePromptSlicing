import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def insert_user(username, password_hash):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, password_hash))
    connection.commit()
    connection.close()

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    password_hash = hash_password(password)
    insert_user(username, password_hash)