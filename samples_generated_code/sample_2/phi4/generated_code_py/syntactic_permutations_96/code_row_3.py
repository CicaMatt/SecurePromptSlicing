import sqlite3
import hashlib

def create_database():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        salted_hash TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256((salt + password).encode()).hexdigest()

def register_user(username, password):
    salt = 'somesalt'
    hashed_password = hash_password(password, salt)
    salted_hash = salt + hashed_password

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("INSERT INTO users (username, salted_hash) VALUES (?, ?)", 
                       (username, salted_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        print(f"User '{username}' already exists.")
    
    conn.close()

def main():
    create_database()
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    register_user(username, password)
    print("Registration successful.")

if __name__ == '__main__':
    main()