import hashlib
import os

def hash_password(password: str) -> str:
    salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt.hex() + key.hex()

username = input("Enter username: ")
password = input("Enter password: ")

hashed_password = hash_password(password)

with open('user_data.txt', 'a') as file:
    file.write(f"{username},{hashed_password}\n")