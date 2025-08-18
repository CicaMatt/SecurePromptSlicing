from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self):
        input_password = getpass("Enter your password: ")
        if input_password == self.password:
            self.logged_in = True
            print(f"Welcome, {self.username}!")
        else:
            print("Login failed. Incorrect password.")

    def change_email(self):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        old_email = input("Enter your current email: ")
        confirm_password = getpass("Confirm your password: ")

        if old_email == self.email and confirm_password == self.password:
            new_email = input("Enter your new email: ")
            self.email = new_email
            print("Email successfully changed.")
        else:
            print("Incorrect email or password. Email not changed.")

# Example usage
user = User("john_doe", "john@example.com", "securepassword")
user.login()
user.change_email()