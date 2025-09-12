import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

user = User("example@example.com", "password123")

def change_email():
    old_email = input("Enter your current email: ")
    if old_email != user.email:
        print("Incorrect current email.")
        return
    
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Enter your password to confirm: ")

    if confirm_password != user.password:
        print("Incorrect password.")
        return

    user.email = new_email
    print("Email successfully changed to:", user.email)

change_email()