import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

user = User("example@example.com", "password123")

def change_email():
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password: ")

    if old_email == user.email and confirm_password == user.password:
        user.email = new_email
        print("Email successfully changed.")
    else:
        print("Incorrect current email or password.")

change_email()