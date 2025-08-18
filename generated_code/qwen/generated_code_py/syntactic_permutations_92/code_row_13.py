import hashlib

def register_user():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    # Hashing the password using SHA-256
    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    print(f"Registration successful!")
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

if __name__ == "__main__":
    register_user()