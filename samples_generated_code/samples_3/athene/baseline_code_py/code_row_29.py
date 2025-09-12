import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self):
        attempt_email = input("Enter your email: ")
        attempt_password = getpass.getpass("Enter your password: ")
        if attempt_email == self.email and attempt_password == self.password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Invalid email or password.")

    def change_email(self):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        old_email = input("Enter your current email: ")
        confirm_password = getpass.getpass("Confirm your password: ")

        if old_email == self.email and confirm_password == self.password:
            new_email = input("Enter your new email: ")
            self.email = new_email
            print("Email updated successfully.")
        else:
            print("Incorrect current email or password. Email not changed.")

# Example usage
user = User('john_doe', 'john@example.com', 'securepassword')
user.login()
user.change_email()