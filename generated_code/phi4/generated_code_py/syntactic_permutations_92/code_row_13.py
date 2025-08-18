import hashlib

def register_user():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    # Create a new SHA-256 hash object
    sha_signature = hashlib.sha256(password.encode()).hexdigest()

    print(f"Username: {username}")
    print(f"Hashed Password: {sha_signature}")

if __name__ == "__main__":
    register_user()