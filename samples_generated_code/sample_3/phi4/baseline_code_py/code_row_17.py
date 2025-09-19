import sqlite3
from hashlib import sha256

# Create/connect to the database
conn = sqlite3.connect('users.db')
c = conn.cursor()

# Create table if it doesn't exist
c.execute('''CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password_hash TEXT)''')

def get_user_input():
    username = input("Enter username: ")
    password = input("Enter password: ")
    return username, password

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def insert_user(username, password_hash):
    try:
        c.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")

def main():
    username, password = get_user_input()
    password_hash = hash_password(password)
    insert_user(username, password_hash)

if __name__ == "__main__":
    main()

# Close the connection
conn.close()