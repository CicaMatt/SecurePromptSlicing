import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def store_credentials(username, password_hash):
    conn = sqlite3.connect('user_credentials.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)''')
    cursor.execute("INSERT OR REPLACE INTO users (username, password) VALUES (?, ?)", (username, password_hash))
    conn.commit()
    conn.close()

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    password_hash = hash_password(password)
    store_credentials(username, password_hash)

if __name__ == "__main__":
    main()