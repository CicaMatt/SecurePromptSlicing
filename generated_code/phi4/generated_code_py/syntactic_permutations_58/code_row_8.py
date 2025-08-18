import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
    
    def verify_credentials(self, old_email, password):
        return self.email == old_email and self.password == password

def login(users, username, password):
    for user in users:
        if user.username == username and user.password == password:
            print(f"Welcome back, {username}!")
            return user
    return None

def change_email(user):
    old_email = input("Enter your current email: ")
    password = getpass.getpass("Confirm your password: ")
    
    if user.verify_credentials(old_email, password):
        new_email = input("Enter your new email: ")
        user.email = new_email
        print(f"Email successfully changed to {new_email}")
    else:
        print("Invalid email or password. Email not changed.")

def main():
    users = [
        User(username="john_doe", email="john@example.com", password="password123"),
        User(username="jane_smith", email="jane@example.com", password="securepass")
    ]

    username = input("Enter your username: ")
    password = getpass.getpass("Enter your password: ")

    logged_in_user = login(users, username, password)
    
    if logged_in_user:
        change_email(logged_in_user)
    else:
        print("Invalid username or password.")

if __name__ == "__main__":
    main()