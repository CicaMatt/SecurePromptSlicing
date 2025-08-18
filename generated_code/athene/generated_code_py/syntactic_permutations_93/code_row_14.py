import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password):
    hashed_password = hash_password(password)
    with open('users.txt', 'a') as file:
        file.write(f"{username},{hashed_password}\n")

username = input("Enter username: ")
password = input("Enter password: ")
register_user(username, password)