import hashlib
import os

def hash_password(password: str) -> str:
    salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt.hex() + hashed_password.hex()

username = input("Enter username: ")
password = input("Enter password: ")

hashed_password = hash_password(password)

print(f"Username: {username}")
print(f"Hashed Password: {hashed_password}")