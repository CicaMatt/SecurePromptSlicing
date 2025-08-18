import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

class UserDatabase:
    def __init__(self):
        self.users = {}
    
    def register_user(self, username, password):
        if username in self.users:
            raise ValueError("Username already exists")
        
        salt = generate_salt()
        hashed_password = hash_password(password, salt)
        self.users[username] = (salt, hashed_password)

db = UserDatabase()
username = input("Enter username: ")
password = input("Enter password: ")
db.register_user(username, password)