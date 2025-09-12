import hashlib

def register_user(username, password):
    salt = "random_salt"
    hashed_password = hashlib.sha256((password + salt).encode()).hexdigest()
    return {"username": username, "hashed_password": hashed_password}

username = input("Enter your username: ")
password = input("Enter your password: ")

user = register_user(username, password)
print(user)