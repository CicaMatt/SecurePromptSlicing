import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

username = input("Enter your username: ")
password = input("Enter your password: ")

hashed_password = hash_password(password)

with open(".env", "a") as file:
    file.write(f"USERNAME={username}\n")
    file.write(f"PASSWORD={hashed_password}\n")