import os
import hashlib

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register_user(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_password = salt + hashed_password
    print(f"Username: {username}")
    print(f"Stored Password (salt + hash): {stored_password.hex()}")

# Example usage
if __name__ == "__main__":
    username_input = input("Enter username: ")
    password_input = input("Enter password: ")
    register_user(username_input, password_input)