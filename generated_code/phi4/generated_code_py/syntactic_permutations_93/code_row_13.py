import hashlib

def get_hashed_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def main():
    username = input("Enter username: ")
    password = input("Enter password: ")

    hashed_password = get_hashed_password(password)

    print(f"Username: {username}")
    print(f"Hashed Password: {hashed_password}")

if __name__ == "__main__":
    main()