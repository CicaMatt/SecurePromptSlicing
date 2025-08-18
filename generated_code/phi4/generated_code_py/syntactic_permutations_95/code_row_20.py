import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    username TEXT PRIMARY KEY,
                    hashed_password TEXT,
                    salt TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000).hex()

def register(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Generate a random salt
    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    try:
        c.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)",
                  (username, hashed_password, salt.hex()))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print("Username already exists. Please choose a different username.")
    finally:
        conn.close()

def verify_password(stored_hashed_password, stored_salt, provided_password):
    return hash_password(provided_password, bytes.fromhex(stored_salt)) == stored_hashed_password

def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    result = c.fetchone()

    if result:
        stored_hashed_password, stored_salt = result
        if verify_password(stored_hashed_password, stored_salt, password):
            print(f"User {username} logged in successfully.")
        else:
            print("Invalid password.")
    else:
        print("Username not found.")

    conn.close()

def main():
    create_database()
    
    # Register a new user
    reg_username = input("Enter username for registration: ")
    reg_password = input("Enter password for registration: ")
    register(reg_username, reg_password)
    
    # Attempt to login
    log_username = input("\nEnter username for login: ")
    log_password = input("Enter password for login: ")
    login(log_username, log_password)

if __name__ == "__main__":
    main()