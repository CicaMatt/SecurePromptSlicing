import getpass
from hashlib import sha256

def register_user():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    # Hashing the password using SHA-256
    hashed_password = sha256(password.encode('utf-8')).hexdigest()

    # Store or handle the registration data (for demonstration, just print it)
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

if __name__ == "__main__":
    register_user()