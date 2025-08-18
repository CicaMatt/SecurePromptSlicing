import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    if not username or not password:
        print("Username and password cannot be empty.")
        return

    hashed_password = hash_password(password)
    
    # Simulate storing in a database
    with open('users.txt', 'a') as f:
        f.write(f"{username},{hashed_password}\n")

    print("Registration successful!")

if __name__ == "__main__":
    register_user()