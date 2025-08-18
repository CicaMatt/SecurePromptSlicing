import hashlib

def register_user():
    username = input("Enter your username: ")
    password = input("Enter your password: ").encode()
    hashed_password = hashlib.sha256(password).hexdigest()
    
    with open('users.txt', 'a') as file:
        file.write(f"{username},{hashed_password}\n")
        
register_user()