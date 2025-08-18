import hashlib
import os

def hash_password(password):
    salt = os.urandom(32)
    key = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + key

username = input("Enter username: ")
password = input("Enter password: ")

hashed_password = hash_password(password)

with open('user_credentials.txt', 'w') as file:
    file.write(f"{username}:{hashed_password.hex()}")