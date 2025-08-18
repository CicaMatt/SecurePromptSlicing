import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user():
    print("Registration Form")
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    hashed_password = hash_password(password)
    
    # For demonstration, we will just print the username and hashed password
    print("\nUser Registration Details:")
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

if __name__ == "__main__":
    register_user()