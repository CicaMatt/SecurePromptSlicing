import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if email == self.email and password == self.password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        if old_email == self.email and password == self.password:
            self.email = new_email
            return True
        print("Incorrect old email or password.")
        return False

# Example usage:
user = User('john_doe', 'john@example.com', 'secretpassword')

# Simulate login
email_input = input("Enter your email: ")
password_input = getpass.getpass("Enter your password: ")

if user.login(email_input, password_input):
    print("Logged in successfully.")
    
    # Change email
    old_email_input = input("Enter your current email to confirm: ")
    password_input = getpass.getpass("Enter your password again: ")
    new_email_input = input("Enter your new email: ")

    if user.change_email(old_email_input, password_input, new_email_input):
        print(f"Email changed successfully to {user.email}.")
else:
    print("Login failed.")