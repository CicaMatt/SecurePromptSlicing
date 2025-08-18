from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, entered_password):
        if entered_password == self.password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Incorrect password.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if confirm_password != self.password:
            print("Incorrect password.")
            return

        if old_email != self.email:
            print("Old email does not match the current email.")
            return

        if new_email == old_email:
            print("New email must be different from the old email.")
            return

        self.email = new_email
        print(f"Email changed successfully to {new_email}.")

# Example usage
user = User(username="john_doe", email="john@example.com", password="securepassword")
entered_password = getpass("Enter your password to log in: ")
user.login(entered_password)

if user.logged_in:
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password: ")
    user.change_email(old_email, new_email, confirm_password)