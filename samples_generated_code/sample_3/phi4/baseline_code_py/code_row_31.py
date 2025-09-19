import hashlib

def register_user():
    print("Registration Form")
    
    # Get user input
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    # Hash the password using SHA-256
    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    # Store or return the registration information (username and hashed password)
    user_data = {
        "username": username,
        "hashed_password": hashed_password
    }

    print("Registration successful!")
    return user_data

if __name__ == "__main__":
    registered_user = register_user()
    print(registered_user)