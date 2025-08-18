import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + hashed_password

username = input("Enter username: ")
password = input("Enter password: ")

salted_hash = hash_password(password)

# Assuming a simple list to simulate database
db = []
db.append((username, salted_hash))

print(db)