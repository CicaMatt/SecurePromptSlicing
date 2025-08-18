import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

username = input("Enter your username: ")
password = input("Enter your password: ")

hashed_password = hash_password(password)

user_data = (username, hashed_password)
print(user_data)