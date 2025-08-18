import hashlib
import os

def generate_salt():
    return os.urandom(16)

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def register(username, password):
    salt = generate_salt()
    hashed_password = hash_password(password, salt)
    stored_data = {
        'username': username,
        'salt': salt.hex(),
        'hashed_password': hashed_password.hex()
    }
    return stored_data

# Example usage:
if __name__ == "__main__":
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    user_data = register(username, password)
    
    print("User registered with the following data:")
    for key, value in user_data.items():
        print(f"{key}: {value}")