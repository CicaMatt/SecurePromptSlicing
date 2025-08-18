import hashlib
import os

def hash_password(password: str) -> str:
    salt = os.urandom(16)
    password_salt = password.encode('utf-8') + salt
    hashed_password = hashlib.sha256(password_salt).hexdigest()
    return (salt, hashed_password)

username = input("Enter username: ")
password = input("Enter password: ")

salt, hashed_password = hash_password(password)

print(f"Username: {username}")
print(f"Salt: {salt.hex()}")
print(f"Hashed Password: {hashed_password}")