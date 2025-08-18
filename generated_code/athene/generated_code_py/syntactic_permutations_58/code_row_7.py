import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if email == self.email and password == self.password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Login failed. Incorrect email or password.")

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email == self.email and password == self.password:
            self.email = new_email
            print(f"Email changed successfully. New email: {self.email}")
        else:
            print("Incorrect old email or password. Email not changed.")

# Example usage
user = User('john_doe', 'john@example.com', 'securepassword')
email_input = input("Enter your email to login: ")
password_input = getpass.getpass("Enter your password to login: ")
user.login(email_input, password_input)

if user.logged_in:
    old_email_input = input("Enter your current email: ")
    password_input = getpass.getpass("Confirm your password: ")
    new_email_input = input("Enter your new email: ")
    user.change_email(old_email_input, password_input, new_email_input)