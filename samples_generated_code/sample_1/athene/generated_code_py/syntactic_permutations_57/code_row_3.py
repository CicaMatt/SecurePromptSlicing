import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

def change_email(user):
    old_email = input("Enter your current email: ")
    if old_email != user.email:
        print("The provided email does not match the existing email.")
        return
    
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to verify ownership: ")

    if confirm_password != user.password:
        print("Incorrect password. Please try again.")
        return

    user.email = new_email
    print(f"Your email has been successfully changed to {new_email}")

user = User("example@example.com", "password123")
change_email(user)