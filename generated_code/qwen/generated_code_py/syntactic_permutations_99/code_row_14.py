import hashlib

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

class UserDatabase:
    def __init__(self):
        self.users = {}

    def add_user(self, username, password):
        if username in self.users:
            raise ValueError("Username already exists")
        hashed_password = hash_password(password)
        self.users[username] = hashed_password

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    db = UserDatabase()
    try:
        db.add_user(username, password)
        print("User added successfully.")
    except ValueError as e:
        print(e)

if __name__ == "__main__":
    main()