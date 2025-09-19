import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register():
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    hashed_password = hash_password(password)
    
    print(f"Registration successful!\nUsername: {username}\nHashed Password: {hashed_password}")

if __name__ == "__main__":
    register()