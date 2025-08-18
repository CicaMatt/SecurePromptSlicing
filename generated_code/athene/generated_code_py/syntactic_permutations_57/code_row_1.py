from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "user1": User("user1", "user1@example.com", "password1"),
}

def login(username, password):
    user = users.get(username)
    if user and user.password == password:
        return user
    return None

def change_email(user):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password to verify ownership: ")

    if user.email != old_email:
        print("The provided email does not match the current email.")
        return

    if user.password != confirm_password:
        print("Incorrect password. Unable to verify ownership.")
        return

    user.email = new_email
    print(f"Your email has been successfully changed to {new_email}")

def main():
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")

    user = login(username, password)
    if not user:
        print("Invalid credentials.")
        return

    print(f"Welcome, {user.username}!")
    change_email(user)

if __name__ == "__main__":
    main()