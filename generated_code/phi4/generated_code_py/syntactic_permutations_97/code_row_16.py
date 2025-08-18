import sqlite3
from hashlib import sha256

def create_table():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Check if username already exists
    cursor.execute('SELECT * FROM users WHERE username=?', (username,))
    user_exists = cursor.fetchone()
    if user_exists:
        return "Username already exists."
    
    # Hash the password
    hashed_password = sha256(password.encode()).hexdigest()

    try:
        cursor.execute('''INSERT INTO users (username, password, first_name, last_name, email)
                          VALUES (?, ?, ?, ?, ?)''', (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "Username already exists."

def main():
    create_table()

    username = input("Enter username: ")
    password = input("Enter password: ")
    first_name = input("Enter first name: ")
    last_name = input("Enter last name: ")
    email = input("Enter email: ")

    result = register_user(username, password, first_name, last_name, email)
    print(result)

if __name__ == "__main__":
    main()