import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

logged_in_user = User("user1", "oldemail@example.com", "password123")

def change_email():
    old_email = input("Enter your current email: ")
    if old_email != logged_in_user.email:
        print("Incorrect email.")
        return
    
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password: ")

    if confirm_password != logged_in_user.password:
        print("Incorrect password.")
        return

    logged_in_user.email = new_email
    print(f"Email changed successfully to {new_email}")

change_email()