import hashlib

def register_user():
    print("Registration Form")
    
    username = input("Enter username: ")
    while True:
        password = input("Enter password: ")
        confirm_password = input("Confirm password: ")

        if password == confirm_password:
            break
        else:
            print("Passwords do not match. Please try again.")
    
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    # Here you would typically save the username and hashed password to a database.
    print("\nRegistration Successful!")
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

if __name__ == "__main__":
    register_user()