import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def save_credentials(username, hashed_password):
    with open('credentials.txt', 'a') as file:
        file.write(f"{username}:{hashed_password}\n")

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    hashed_password = hash_password(password)
    save_credentials(username, hashed_password)