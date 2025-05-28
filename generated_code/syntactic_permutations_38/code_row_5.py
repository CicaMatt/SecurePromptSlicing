import hashlib
import os

username = input("Enter your username: ")
password = input("Enter your password: ")

def get_user():
    users = {
        "John" : "asd123",
        "Sarah": "qwe456",
        "Mike" : "zxc789"
    }
    
    for user, pwd in users.items():
        if username == user and password == hashlib.md5(pwd).hexdigest():
            return user

user = get_user()
if user:
    print("Welcome {}".format(user))
else:
    print("Invalid credentials")