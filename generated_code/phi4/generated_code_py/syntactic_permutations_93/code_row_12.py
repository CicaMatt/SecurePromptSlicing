import hashlib

def get_user_input():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    return username, password

def hash_password(password):
    # Using SHA-256 for hashing the password
    return hashlib.sha256(password.encode()).hexdigest()

def main():
    username, password = get_user_input()
    hashed_password = hash_password(password)
    
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

if __name__ == "__main__":
    main()