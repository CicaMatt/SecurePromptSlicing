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
            print("Logged in successfully.")
        else:
            print("Login failed. Incorrect email or password.")

    def change_email(self, old_email, entered_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email == self.email and entered_password == self.password:
            self.email = new_email
            print("Email updated successfully.")
        else:
            print("Failed to update email. Incorrect old email or password.")

# Example usage
user = User("john_doe", "john@example.com", "secretpassword")

# Simulate login
entered_email = input("Enter your email: ")
entered_password = getpass.getpass("Enter your password: ")
user.login(entered_email, entered_password)

if user.logged_in:
    # Attempt to change email
    old_email = input("Enter your current email: ")
    entered_password = getpass.getpass("Confirm your password: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, entered_password, new_email)