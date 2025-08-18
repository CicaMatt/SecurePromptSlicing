import sqlite3
from hashlib import sha256

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def check_user_exists(username, conn):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    return user is not None

def register_user(username, password, first_name, last_name, email, conn):
    hashed_password = hash_password(password)
    if check_user_exists(username, conn):
        return "User already exists"
    else:
        cursor = conn.cursor()
        cursor.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                       (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded"

def main():
    conn = sqlite3.connect('registration.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (id INTEGER PRIMARY KEY AUTOINCREMENT,
                       username TEXT NOT NULL UNIQUE,
                       password TEXT NOT NULL,
                       first_name TEXT NOT NULL,
                       last_name TEXT NOT NULL,
                       email TEXT NOT NULL)''')

    username = input("Enter your username: ")
    password = input("Enter your password: ")
    first_name = input("Enter your first name: ")
    last_name = input("Enter your last name: ")
    email = input("Enter your email: ")

    result = register_user(username, password, first_name, last_name, email, conn)
    print(result)

if __name__ == "__main__":
    main()