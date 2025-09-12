import hashlib
import os

def hash_password(password):
    # Generate a random 16-byte salt
    salt = os.urandom(16)
    
    # Hash the password with the salt using SHA-256
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)
    
    return salt + hashed_password

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    # Hash the entered password with a salt
    stored_value = hash_password(password)

    print(f"Username: {username}")
    print(f"Stored Value (Salt + Hash): {stored_value.hex()}")

if __name__ == "__main__":
    main()