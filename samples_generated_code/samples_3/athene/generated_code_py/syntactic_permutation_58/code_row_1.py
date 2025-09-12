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

    def change_email(self):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        old_email = getpass.getpass("Enter your current email: ")
        password = getpass.getpass("Confirm your password: ")

        if old_email == self.email and password == self.password:
            new_email = input("Enter your new email: ")
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Incorrect old email or password. Email not changed.")

# Example usage
user = User("john_doe", "john@example.com", "securepassword")
user.login("john@example.com", "securepassword")
user.change_email()