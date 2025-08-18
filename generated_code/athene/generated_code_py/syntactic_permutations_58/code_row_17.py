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
            self.logged_in = False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return
        if old_email == self.email and password == self.password:
            self.email = new_email
            print(f"Email changed successfully. New email: {self.email}")
        else:
            print("Failed to change email. Incorrect old email or password.")

# Example usage
user = User("john_doe", "john@example.com", "password123")
entered_email = input("Enter your email: ")
entered_password = getpass.getpass("Enter your password: ")
user.login(entered_email, entered_password)

if user.logged_in:
    old_email = input("Enter your current email to confirm: ")
    password = getpass.getpass("Enter your password to confirm: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, password, new_email)