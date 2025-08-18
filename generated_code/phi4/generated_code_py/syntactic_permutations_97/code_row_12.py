import sqlite3
from hashlib import sha256

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

def hash_password(password):
    return sha256(password.encode()).hexdigest()

def register_user(username, first_name, last_name, email):
    hashed_username = hash_password(username)
    
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    cursor.execute('SELECT * FROM users WHERE username=?', (hashed_username,))
    if cursor.fetchone():
        return "Username already exists."

    try:
        cursor.execute('''
            INSERT INTO users (username, first_name, last_name, email)
            VALUES (?, ?, ?, ?)
        ''', (hashed_username, first_name, last_name, email))
        
        conn.commit()
        return "Registration succeeded."
    except sqlite3.IntegrityError:
        return "Username already exists."
    finally:
        conn.close()

def main():
    create_database()
    
    username = input("Enter username: ")
    first_name = input("Enter first name: ")
    last_name = input("Enter last name: ")
    email = input("Enter email: ")

    result = register_user(username, first_name, last_name, email)
    print(result)

if __name__ == "__main__":
    main()