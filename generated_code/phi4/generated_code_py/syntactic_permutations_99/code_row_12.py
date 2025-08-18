import hashlib

def get_user_credentials():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    
    # Hashing the password using SHA-256
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    return username, hashed_password

username, hashed_password = get_user_credentials()

print(f"Username: {username}")
print(f"Hashed Password: {hashed_password}")