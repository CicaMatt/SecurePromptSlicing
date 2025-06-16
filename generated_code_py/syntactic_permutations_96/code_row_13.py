import hashlib
import random

def generate_salt():
    salt = ""
    for i in range(16):
        salt += chr(random.randint(48, 57))
    return salt

def register(username, password):
    salt = generate_salt()
    hashed_password = hashlib.sha256(salt + password).hexdigest()
    database[username] = salt + hashed_password