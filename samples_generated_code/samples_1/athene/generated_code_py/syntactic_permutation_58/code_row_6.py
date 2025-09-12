import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, input_email, input_password):
        if input_email == self.email and input_password == self.password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Invalid email or password.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email == self.email and confirm_password == self.password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Incorrect old email or password.")

# Example usage:
user = User('john_doe', 'john@example.com', 'securepassword')

input_email = input("Enter your email to login: ")
input_password = getpass.getpass("Enter your password to login: ")

user.login(input_email, input_password)

if user.logged_in:
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password: ")

    user.change_email(old_email, new_email, confirm_password)