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

    def change_email(self):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        old_email = input("Enter your current email: ")
        password = getpass.getpass("Confirm your password: ")

        if old_email == self.email and password == self.password:
            new_email = input("Enter your new email: ")
            self.email = new_email
            print("Email updated successfully.")
        else:
            print("Incorrect old email or password. Email not changed.")

# Example usage:
user = User("john_doe", "john@example.com", "securepassword")
if user.login(input("Login - Enter your email: "), getpass.getpass("Login - Enter your password: ")):
    user.change_email()