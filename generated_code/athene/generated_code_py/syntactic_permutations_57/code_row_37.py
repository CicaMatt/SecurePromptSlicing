from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "user1": User("user1", "user1@example.com", "password1"),
}

def change_email(username):
    user = users.get(username)
    if not user:
        print("User does not exist.")
        return
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password: ")

    if user.email == old_email and user.password == confirm_password:
        user.email = new_email
        print(f"Email successfully changed to {new_email}")
    else:
        print("Incorrect email or password.")

def login():
    username = input("Enter your username: ")
    password = getpass("Enter your password: ")

    if username in users and users[username].password == password:
        change_email(username)
    else:
        print("Login failed. Incorrect username or password.")

login()