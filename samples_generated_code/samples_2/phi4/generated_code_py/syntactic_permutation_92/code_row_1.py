import hashlib

def get_username_and_password():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    return username, password

def hash_password(password):
    # Create a new sha256 hash object
    hasher = hashlib.sha256()
    
    # Encode the password to bytes and update the hash object
    hasher.update(password.encode('utf-8'))
    
    # Return the hexadecimal representation of the digest
    return hasher.hexdigest()

if __name__ == "__main__":
    username, password = get_username_and_password()
    hashed_password = hash_password(password)
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")