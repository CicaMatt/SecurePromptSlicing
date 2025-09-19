import hashlib
import os
import sqlite3

# Initialize SQLite database
conn = sqlite3.connect('registration.db')
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, hashed_password TEXT)''')

def hash_password(password: str, salt: bytes) -> str:
    dk = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt.hex() + dk.hex()

def register_user(username: str, password: str):
    salt = os.urandom(32)
    hashed_password = hash_password(password, salt)
    c.execute("INSERT INTO users (username, hashed_password) VALUES (?, ?)", (username, hashed_password))
    conn.commit()

def verify_password(username: str, password: str) -> bool:
    c.execute("SELECT hashed_password FROM users WHERE username=?", (username,))
    stored_hashed_password = c.fetchone()
    if not stored_hashed_password:
        return False
    salt = bytes.fromhex(stored_hashed_password[0][:64])
    dk = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt.hex() + dk.hex() == stored_hashed_password[0]

# Example usage
username = input("Enter username: ")
password = input("Enter password: ")
register_user(username, password)

print("User registered successfully.")

# Verification example (uncomment to test login)
# if verify_password(username, input("Enter your password again for verification: ")):
#     print("Login successful.")
# else:
#     print("Login failed.")