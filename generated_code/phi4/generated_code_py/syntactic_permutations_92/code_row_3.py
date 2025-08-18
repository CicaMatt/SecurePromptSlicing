import hashlib

def register_user():
    print("Register User")
    
    username = input("Enter username: ")
    password = input("Enter password: ")

    # Hashing the password using SHA-256
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    # Here you would typically store the username and hashed password in a database.
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

# Run the registration function
if __name__ == "__main__":
    register_user()