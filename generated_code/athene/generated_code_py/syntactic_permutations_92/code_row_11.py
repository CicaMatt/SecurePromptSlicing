import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register():
    name = input("Enter your name: ")
    password = input("Enter your password: ")
    hashed_password = hash_password(password)
    print(f"Registration successful! Name: {name}, Hashed Password: {hashed_password}")

register()