import hashlib

def register_user():
    print("Registration Form")
    
    # Get username input
    username = input("Enter your username: ").strip()
    
    # Get password input
    password = input("Enter your password: ")
    
    # Hash the password using SHA-256
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    print("\nRegistration Complete")
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

# Run the registration function
register_user()