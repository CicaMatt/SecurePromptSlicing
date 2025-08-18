import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register():
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    hashed_password = hash_password(password)
    
    # Here you would typically store the username and hashed password in a database
    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

if __name__ == "__main__":
    register()