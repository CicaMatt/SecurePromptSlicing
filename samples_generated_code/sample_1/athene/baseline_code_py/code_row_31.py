import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    hashed_password = hash_password(password)
    print(f"User registered successfully!\nUsername: {username}\nHashed Password: {hashed_password}")

register_user()