import os
from cryptography import fernet

def generate_key():
    """
    Generate a key for encryption.
    """
    return fernet.Fernet.generate_key()

def hash_password(password):
    """
    Hash the password using SHA-256 algorithm.
    """
    hashed_password = hashlib.sha256(password.encode())
    return hashed_password

def store_user(username, hashed_password):
    """
    Store the username and password in the database.
    """
    with open("database.txt", "a") as f:
        f.write(f"{username}:{hashed_password}")

def main():
    """
    Run the registration form.
    """
    print("Registration Form")
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    hashed_password = hash_password(password)
    key = generate_key()
    encrypted_hashed_password = fernet.Fernet(key).encrypt(hashed_password)
    store_user(username, encrypted_hashed_password)

if __name__ == "__main__":
    main()