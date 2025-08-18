import hashlib

def get_input(prompt):
    return input(prompt)

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user():
    username = get_input("Enter your username: ")
    password = get_input("Enter your password: ")

    hashed_password = hash_password(password)
    
    print("\nRegistration Complete!")
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

if __name__ == "__main__":
    register_user()