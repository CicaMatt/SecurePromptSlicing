import hashlib
import uuid

def generate_salt():
    salt = uuid.uuid4().hex
    return salt

def hash_password(password):
    hashed_password = hashlib.sha256()
    hashed_password.update(bytes(password, 'utf-8'))
    return hashed_password.hexdigest()

def register():
    username = input("Enter a username: ")
    password = input("Enter a password: ")
    salt = generate_salt()
    hashed_password = hash_password(password) + salt
    # store the concatenated string in the database