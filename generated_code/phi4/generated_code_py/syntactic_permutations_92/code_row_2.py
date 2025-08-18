import hashlib
from getpass import getpass

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user():
    print("Register a new account")
    username = input("Enter username: ")
    password = getpass("Enter password: ")

    hashed_password = hash_password(password)
    
    # In real applications, you'd store the username and hashed password in a database
    with open('users.txt', 'a') as f:
        f.write(f"{username},{hashed_password}\n")
    
    print("Registration successful!")

if __name__ == "__main__":
    register_user()