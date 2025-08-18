import hashlib
import os

def hash_password(password, salt):
    return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    salt = os.urandom(16)
    hashed_password = hash_password(password, salt)

    print(f"Username: {username}")
    print(f"Salt: {salt.hex()}")
    print(f"Hashed Password: {hashed_password.hex()}")

if __name__ == "__main__":
    main()