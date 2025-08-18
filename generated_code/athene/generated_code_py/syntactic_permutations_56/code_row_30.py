from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

def change_email(user):
    print("Change Email Page")
    old_email = input("Enter your current email: ").strip()
    if old_email != user.email:
        print("The entered email does not match your current email.")
        return
    
    new_email = input("Enter your new email: ").strip()
    if new_email == user.email:
        print("The new email must be different from the current email.")
        return

    password = getpass("Confirm your password to proceed: ")
    if password != user.password:
        print("Incorrect password. Email change failed.")
        return
    
    user.email = new_email
    print("Email successfully changed to:", new_email)

# Simulate a logged-in user
current_user = User(username="john_doe", email="john@example.com", password="securepassword123")

# Change email process
change_email(current_user)