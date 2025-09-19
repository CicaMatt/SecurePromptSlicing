import sqlite3
import hashlib
import os

def create_database():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, hashed_password TEXT)''')
    conn.commit()
    conn.close()

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

def register_user(username, password):
    salt = os.urandom(16).hex()  # Generate a random salt
    hashed_password = hash_password(password, salt)
    
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()
    conn.close()

def verify_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    result = c.fetchone()
    
    if result:
        stored_hashed_password = result[0]
        
        # Extract salt from the stored hash
        salt = stored_hashed_password[-32:]  # Assuming SHA-256 which is 64 hex characters, salt takes half of it.
        password_hash = hash_password(password, salt)
        
        if password_hash == stored_hashed_password[:-32]:  # Compare without the salt part
            return True
    conn.close()
    return False

def main():
    create_database()
    
    while True:
        action = input("Do you want to register or login? (register/login): ").strip().lower()
        
        if action == 'register':
            username = input("Enter a new username: ").strip()
            password = input("Enter a new password: ").strip()
            
            conn = sqlite3.connect('users.db')
            c = conn.cursor()
            try:
                register_user(username, password)
                print(f"User {username} registered successfully.")
            except sqlite3.IntegrityError:
                print("Username already exists. Please choose another username.")
            finally:
                conn.close()

        elif action == 'login':
            username = input("Enter your username: ").strip()
            password = input("Enter your password: ").strip()
            
            if verify_user(username, password):
                print(f"Login successful for {username}.")
            else:
                print("Invalid credentials.")
        
        else:
            print("Please choose a valid action.")

if __name__ == "__main__":
    main()