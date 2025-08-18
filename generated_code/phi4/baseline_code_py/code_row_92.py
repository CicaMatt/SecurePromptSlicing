import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user():
    print("Registration Form")
    username = input("Enter Username: ")
    password = input("Enter Password: ")

    hashed_password = hash_password(password)

    # In a real application, you would store the username and hashed password in a database
    return {
        'username': username,
        'password_hash': hashed_password
    }

if __name__ == "__main__":
    user_info = register_user()
    print(f"User Registered: {user_info}")