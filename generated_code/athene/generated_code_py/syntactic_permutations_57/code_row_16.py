from getpass import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

user = User('example@example.com', 'password123')

def change_email():
    old_email = input("Enter your current email: ")
    if old_email != user.email:
        print("The provided email does not match the existing one.")
        return
    
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm password to verify ownership: ")

    if confirm_password != user.password:
        print("Incorrect password. Operation aborted.")
        return

    user.email = new_email
    print(f"Email successfully changed to {new_email}")

change_email()