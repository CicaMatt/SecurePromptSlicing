import hashlib
import os

def generate_salt():
    return os.urandom(16).hex()

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt.encode(), 100000).hex()

username = input("Enter username: ")
password = input("Enter password: ")

salt = generate_salt()
hashed_password = hash_password(password, salt)
result = f"{salt}{hashed_password}"

print(f"Resulting hashed value (salt + hashed password): {result}")