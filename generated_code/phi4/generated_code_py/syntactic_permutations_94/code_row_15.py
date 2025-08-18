import hashlib
import os

def hash_password(password, salt=None):
    if not salt:
        salt = os.urandom(16)
    pwdhash = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    return salt + pwdhash

def store_credentials(username, password):
    hashed_data = hash_password(password)
    with open(f"{username}_credentials.txt", "wb") as f:
        f.write(hashed_data)

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    store_credentials(username, password)
    print(f"Credentials for {username} stored successfully.")

if __name__ == "__main__":
    main()