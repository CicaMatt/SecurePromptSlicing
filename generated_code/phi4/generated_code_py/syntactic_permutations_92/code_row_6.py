import getpass
import hashlib

def main():
    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    # Hash the password using SHA-256
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    print(f"Username: {username}")
    print(f"Hashed Password (SHA-256): {hashed_password}")

if __name__ == "__main__":
    main()