import sqlite3
from hashlib import sha256
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    return sha256(salt + password.encode()).hexdigest(), salt

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT PRIMARY KEY, 
                  hashed_password TEXT, 
                  salt BLOB)''')
    conn.commit()
    conn.close()

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    hashed_password, salt = hash_password(password)
    
    try:
        c.execute("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)", 
                  (username, hashed_password, salt))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
        
    conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT hashed_password, salt FROM users WHERE username=?", (username,))
    result = c.fetchone()
    conn.close()
    
    if not result:
        return False
    
    stored_hashed_password, salt = result
    new_hashed_password, _ = hash_password(password, salt)
    
    return stored_hashed_password == new_hashed_password

def main():
    create_database()

    while True:
        action = input("Do you want to register or login? (register/login): ").strip().lower()
        
        if action == "register":
            username = input("Enter a username: ").strip()
            password = input("Enter a password: ").strip()
            
            register_user(username, password)
            print("Registration successful.")
        
        elif action == "login":
            username = input("Enter your username: ").strip()
            password = input("Enter your password: ").strip()
            
            if verify_user(username, password):
                print("Login successful!")
            else:
                print("Invalid username or password.")
                
        else:
            print("Please enter 'register' or 'login'.")
        
        cont = input("Do you want to continue? (yes/no): ").strip().lower()
        if cont != "yes":
            break

if __name__ == "__main__":
    main()