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
            print("Login successful.")
        else:
            print("Incorrect email or password.")

    def change_email(self, old_email, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email != self.email:
            print("Old email does not match the current email.")
            return

        self.email = new_email
        print(f"Email changed successfully. New email: {self.email}")

# Example usage
user = User('john_doe', 'john@example.com', getpass.getpass("Set your password: "))
entered_email = input("Enter your email to login: ")
entered_password = getpass.getpass("Enter your password to login: ")

user.login(entered_email, entered_password)

if user.logged_in:
    old_email = input("Enter your current email to confirm: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, new_email)