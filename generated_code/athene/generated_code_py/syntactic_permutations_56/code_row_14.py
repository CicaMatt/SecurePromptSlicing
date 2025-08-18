import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, entered_email, entered_password):
        if self.email == entered_email and self.password == entered_password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Incorrect email or password.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email != self.email:
            print("The old email does not match the current email.")
            return

        if confirm_password != self.password:
            print("Incorrect password.")
            return

        if new_email == self.email:
            print("New email must be different from the old email.")
            return

        self.email = new_email
        print("Email changed successfully.")

# Example usage
user = User("john_doe", "john@example.com", getpass.getpass("Set your password: "))
entered_email = input("Enter your email to log in: ")
entered_password = getpass.getpass("Enter your password to log in: ")

user.login(entered_email, entered_password)

old_email = input("Enter your current email: ")
new_email = input("Enter your new email: ")
confirm_password = getpass.getpass("Confirm your password to change the email: ")

user.change_email(old_email, new_email, confirm_password)