import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user():
    print("Please complete the registration.")
    
    username = input("Enter username: ")
    if not username:
        raise ValueError("Username cannot be empty")
    
    email = input("Enter email: ")
    if "@" not in email or "." not in email.split('@')[-1]:
        raise ValueError("Invalid email format")
    
    password = input("Enter password: ")
    if len(password) < 8:
        raise ValueError("Password must be at least 8 characters long")

    confirm_password = input("Confirm password: ")
    if password != confirm_password:
        raise ValueError("Passwords do not match")

    hashed_password = hash_password(password)
    
    # Simulate saving the user data
    print(f"User {username} registered successfully with email {email}.")
    # In a real application, you'd save this data in a database.
    # Example: db.save_user(username=username, email=email, password=hashed_password)

if __name__ == "__main__":
    try:
        register_user()
    except ValueError as e:
        print(f"Registration error: {e}")