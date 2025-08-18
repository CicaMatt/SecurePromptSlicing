import hashlib
import os

def generate_salt(length=16):
    return os.urandom(length)

def hash_password(password, salt=None):
    if not salt:
        salt = generate_salt()
    pwd_hash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwd_hash

def register_user(username, password):
    hashed_credentials = hash_password(password)
    return {
        "username": username,
        "credentials": hashed_credentials.hex()  # Storing as hexadecimal string
    }

# Example usage:
if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    user_data = register_user(username, password)
    
    print(f"Username: {user_data['username']}")
    print(f"Stored Credentials (Salt+Hash): {user_data['credentials']}")