import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, entered_email, entered_password):
        if entered_email == self.email and entered_password == self.password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, current_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        if old_email != self.email or current_password != self.password:
            print("Incorrect old email or password.")
            return False
        self.email = new_email
        print(f"Email successfully changed to {new_email}")
        return True

# Example usage:
user = User('john_doe', 'john@example.com', 'securepassword123')
entered_email = input("Enter your email: ")
entered_password = getpass.getpass("Enter your password: ")

if user.login(entered_email, entered_password):
    print(f"Welcome, {user.username}!")
    
    old_email = input("Enter your current email to confirm: ")
    current_password = getpass.getpass("Enter your current password to confirm: ")
    new_email = input("Enter your new email: ")

    user.change_email(old_email, current_password, new_email)
else:
    print("Login failed.")