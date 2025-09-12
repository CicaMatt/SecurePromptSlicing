import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    hashed_password = hash_password(password)
    print(f"Registered with Username: {username} and Hashed Password: {hashed_password}")

if __name__ == "__main__":
    register_user()