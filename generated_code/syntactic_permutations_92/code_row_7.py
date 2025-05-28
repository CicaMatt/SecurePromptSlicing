import hashlib

def register():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    return (username, hashlib.sha256(password))

register()