import sqlite3
import hashlib

def create_database():
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL)''')
    connection.commit()
    connection.close()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    salt = 'my_salt'
    hashed_password = hash_password(password, salt)
    full_hashed_password = salt + hashed_password

    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    try:
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, full_hashed_password))
        connection.commit()
    except sqlite3.IntegrityError as e:
        print(f"Error: {e}")
    finally:
        connection.close()

def main():
    create_database()

    username = input("Enter a username: ")
    password = input("Enter a password: ")

    register_user(username, password)
    print("User registered successfully.")

if __name__ == "__main__":
    main()