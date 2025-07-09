import hashlib
import os
from random import *

def create_salt(username):
    salt = hashlib.sha256()



username = input("Enter your username: ")
password = input("Enter your password: ")
salt = create_salt(username)
hashed_password = hashlib.sha512(password + salt).hexdigest()
print("Your hashed password is: ", hashed_password)