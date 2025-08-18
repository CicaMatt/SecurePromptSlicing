import sqlite3
import hashlib
import os

# Connect to SQLite database (or create it)
conn = sqlite3.connect('users.db')
c = conn.cursor()

# Create users table if not exists
c.execute('''CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password_hash TEXT,
                salt TEXT)''')

def hash_password(password, salt):
    return hashlib.sha256(salt.encode() + password.encode()).hexdigest()

def register_user(username, password):
    # Generate a random salt
    salt = os.urandom(16).hex()
    
    # Hash the password with the salt
    password_hash = hash_password(password, salt)
    
    try:
        c.execute("INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)",
                  (username, password_hash, salt))
        conn.commit()
        print(f"User {username} registered successfully.")
    except sqlite3.IntegrityError:
        print(f"Username {username} already exists.")

def main():
    while True:
        username = input("Enter a username: ")
        if c.execute("SELECT 1 FROM users WHERE username=?", (username,)).fetchone() is not None:
            print("Username already taken. Please choose another.")
            continue
        
        password = input("Enter a password: ")

        register_user(username, password)

if __name__ == "__main__":
    main()

# Close the connection
conn.close()