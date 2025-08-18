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
            print("Invalid credentials.")

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email == self.email and password == self.password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Incorrect old email or password.")

# Example usage
user = User('john_doe', 'john@example.com', 'securepassword')
input_email = input("Enter your email: ")
input_password = getpass.getpass("Enter your password: ")
user.login(input_email, input_password)

if user.logged_in:
    old_email = input("Enter your current email to confirm: ")
    password = getpass.getpass("Enter your password to confirm: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, password, new_email)