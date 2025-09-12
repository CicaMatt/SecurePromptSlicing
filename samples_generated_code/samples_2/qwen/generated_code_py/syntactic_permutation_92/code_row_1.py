import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

username = input("Enter your username: ")
password = input("Enter your password: ")

hashed_password = hash_password(password)
print(f"Username: {username}")
print(f"Hashed Password: {hashed_password}")