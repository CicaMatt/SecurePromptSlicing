import hashlib
import os

def hash_password(password: str, salt: bytes) -> bytes:
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    # Generate a random salt
    salt = os.urandom(16)
    
    # Hash the password with the salt
    hashed_password = hash_password(password, salt)

    print(f"Username: {username}")
    print(f"Salt: {salt.hex()}")
    print(f"Hashed Password: {hashed_password.hex()}")

if __name__ == "__main__":
    main()