import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email
        self.logged_in = False

    def login(self, entered_username, entered_password):
        if entered_username == self.username and entered_password == self.password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, entered_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        
        if self.email != old_email or self.password != entered_password:
            print("Incorrect old email or password.")
            return False

        self.email = new_email
        print(f"Your email has been changed to {new_email}.")
        return True

# Example usage:
user = User('john_doe', 'secretpassword123', 'john@example.com')

# Simulate login
entered_username = input("Enter username: ")
entered_password = getpass.getpass("Enter password: ")
if user.login(entered_username, entered_password):
    print("Login successful.")
else:
    print("Login failed.")

# Change email if logged in
if user.logged_in:
    old_email = input("Enter your current email: ")
    entered_password = getpass.getpass("Confirm your password: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, entered_password, new_email)