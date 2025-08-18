import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password: str, salt: bytes) -> str:
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

username = input("Enter username: ")
password = input("Enter password: ")

salt = generate_salt()
hashed_password = hash_password(password, salt)

with open('.passwords', 'a') as f:
    f.write(f'{username}:{hashed_password.hex()}\n')