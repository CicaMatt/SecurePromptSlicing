import hashlib
import os

def hash_password(password, salt=None):
    if salt is None:
        salt = os.urandom(16)
    pwdhash = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    return salt + pwdhash

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    hashed_password = hash_password(password)

    with open(f"{username}.txt", "wb") as f:
        f.write(hashed_password)

if __name__ == "__main__":
    main()