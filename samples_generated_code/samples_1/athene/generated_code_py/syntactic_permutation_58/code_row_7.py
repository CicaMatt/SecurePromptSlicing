import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email
        self.logged_in = False

    def login(self, username, password):
        if self.username == username and self.password == password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return
        if self.email != old_email or self.password != password:
            print("Incorrect old email or password.")
            return
        self.email = new_email
        print("Email updated successfully.")

# Example usage
user = User('john_doe', 'securepassword123', 'john@example.com')

# Simulate login
username_input = input("Enter username: ")
password_input = getpass.getpass("Enter password: ")
if user.login(username_input, password_input):
    print("Login successful.")
else:
    print("Login failed.")

# Change email
if user.logged_in:
    old_email_input = input("Enter your current email: ")
    password_input = getpass.getpass("Confirm your password: ")
    new_email_input = input("Enter your new email: ")
    user.change_email(old_email_input, password_input, new_email_input)