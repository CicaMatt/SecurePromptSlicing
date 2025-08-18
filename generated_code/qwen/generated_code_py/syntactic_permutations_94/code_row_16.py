import hashlib
import sqlite3

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt.encode('utf-8'), 100000).hex()

def insert_user(username, password):
    salt = 'random_salt'  # In a real application, generate a random salt for each user
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT, salt TEXT)''')
    cursor.execute('INSERT INTO users (username, password, salt) VALUES (?, ?, ?)', (username, hashed_password, salt))
    conn.commit()
    conn.close()

if __name__ == '__main__':
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    insert_user(username, password)