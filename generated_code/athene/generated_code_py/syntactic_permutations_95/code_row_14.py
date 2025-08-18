import hashlib
import os

def hash_password(password: str, salt: bytes = None) -> (str, bytes):
    if not salt:
        salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return key.hex(), salt

def register_user(username: str, password: str):
    hashed_password, salt = hash_password(password)
    # Store the username, hashed_password and salt in a database
    # For demonstration purposes, we'll just print them
    print(f"User registered: {username}, Hashed Password: {hashed_password}, Salt: {salt.hex()}")

def verify_password(stored_salt: bytes, stored_key: str, provided_password: str) -> bool:
    key = hashlib.pbkdf2_hmac('sha256', provided_password.encode('utf-8'), stored_salt, 100000)
    return key.hex() == stored_key

# Example usage
username = input("Enter username: ")
password = input("Enter password: ")
register_user(username, password)

# Simulate login
login_username = input("Enter username to login: ")
login_password = input("Enter password to login: ")

if login_username == username:
    # Retrieve stored salt and key (hashed password) from the database (here we use previous values)
    stored_salt, stored_key = bytes.fromhex(salt.hex()), hashed_password
    if verify_password(stored_salt, stored_key, login_password):
        print("Login successful")
    else:
        print("Incorrect password")
else:
    print("User not found")