import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email
        self.logged_in = False

    def login(self, password):
        if self.password == password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Incorrect password. Login failed.")

    def change_email(self, old_email, new_email, password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if self.email != old_email:
            print("The entered old email does not match the current email.")
            return

        if self.password != password:
            print("Incorrect password. Email change failed.")
            return

        self.email = new_email
        print(f"Email changed successfully to {self.email}.")

# Example usage
user = User(username="example_user", password="securepassword123", email="oldemail@example.com")

# Simulate login
user.login(getpass.getpass("Enter your password to log in: "))

# Simulate email change
if user.logged_in:
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    password = getpass.getpass("Confirm your password to change the email: ")
    user.change_email(old_email, new_email, password)