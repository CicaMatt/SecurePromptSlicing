import bcrypt
import sqlite3

def hash_password(password):
    salt = bcrypt.gensalt()
    return bcrypt.hashpw(password.encode('utf-8'), salt)

def insert_user(username, password_hash):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, password TEXT)''')
    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password_hash))
    conn.commit()
    conn.close()

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    password_hash = hash_password(password)
    insert_user(username, password_hash)

if __name__ == "__main__":
    main()