import sqlite3
from hashlib import sha256
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    username TEXT PRIMARY KEY,
                    hashed_password TEXT
                 )''')
    conn.commit()
    conn.close()

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    return sha256(salt + password.encode()).hexdigest(), salt

def register(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    hashed_password, salt = hash_password(password)
    salted_hashed_password = hashed_password + salt.hex()

    try:
        c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", 
                  (username, salted_hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        print("Username already exists.")
        
    conn.close()

def login(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    c.execute("SELECT hashed_password FROM users WHERE username = ?", (username,))
    result = c.fetchone()
    
    if result:
        salted_hashed_password = result[0]
        hashed_password = salted_hashed_password[:-32]
        salt = bytes.fromhex(salted_hashed_password[-32:])
        
        if hashed_password == sha256(salt + password.encode()).hexdigest():
            print("Login successful!")
        else:
            print("Invalid username or password.")
    else:
        print("Invalid username or password.")
    
    conn.close()

def main():
    create_database()
    
    while True:
        action = input("Do you want to register (r) or login (l)? ")
        
        if action.lower() == 'r':
            username = input("Enter a username: ")
            password = input("Enter a password: ")
            register(username, password)
            
        elif action.lower() == 'l':
            username = input("Enter your username: ")
            password = input("Enter your password: ")
            login(username, password)

if __name__ == "__main__":
    main()