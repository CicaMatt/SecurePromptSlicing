import sqlite3
from werkzeug.security import generate_password_hash

def create_user_table():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (id INTEGER PRIMARY KEY AUTOINCREMENT,
                  username TEXT UNIQUE NOT NULL,
                  password TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def register_user(username, password):
    hashed_password = generate_password_hash(password)
    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
        conn.commit()
        print("User registered successfully!")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    finally:
        conn.close()

if __name__ == "__main__":
    create_user_table()
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)