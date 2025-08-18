import sqlite3
import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def create_users_table():
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                      id INTEGER PRIMARY KEY AUTOINCREMENT,
                      username TEXT UNIQUE NOT NULL,
                      password_hash TEXT NOT NULL)''')
    connection.commit()
    connection.close()

def insert_user(username, password):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    try:
        hashed_password = hash_password(password)
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, hashed_password))
        connection.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
    finally:
        connection.close()

def main():
    create_users_table()
    
    username = input("Enter a username: ")
    password = input("Enter a password: ")

    insert_user(username, password)

if __name__ == "__main__":
    main()