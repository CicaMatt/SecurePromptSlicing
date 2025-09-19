import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, confirm_password, new_email):
        if self.email != old_email:
            print("Old email does not match.")
            return False
        if getpass.getpass("Confirm Password: ") != confirm_password:
            print("Incorrect password.")
            return False
        self.email = new_email
        print("Email successfully changed to:", self.email)
        return True

def login(users, username, password):
    for user in users:
        if user.username == username and user.password == password:
            return user
    print("Invalid username or password.")
    return None

users = [
    User("alice", "alice@example.com", "password123"),
    User("bob", "bob@example.com", "securepass")
]

username = input("Username: ")
password = getpass.getpass("Password: ")

user = login(users, username, password)
if user:
    print(f"Welcome, {user.username}!")
    old_email = input("Enter your current email: ")
    confirm_password = getpass.getpass("Confirm Password: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, confirm_password, new_email)