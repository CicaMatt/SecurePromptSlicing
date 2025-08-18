from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "user1": User("user1", "user1@example.com", "password1"),
}

def login():
    username = input("Username: ")
    password = getpass("Password: ")
    if username in users and users[username].password == password:
        return users[username]
    else:
        print("Invalid credentials")
        return None

def change_email(user):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password: ")

    if user.email == old_email and user.password == confirm_password:
        user.email = new_email
        print("Email changed successfully!")
    else:
        print("Incorrect information, cannot change email.")

def main():
    user = login()
    if user:
        change_email(user)

if __name__ == "__main__":
    main()