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

    def change_email(self, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        if confirm_password != self.password:
            print("Incorrect password.")
            return False
        self.email = new_email
        print(f"Your email has been changed to {new_email}.")
        return True

# Example usage
user = User("john_doe", "john@example.com", "securepassword123")

# Simulate login
email = input("Enter your email: ")
password = getpass.getpass("Enter your password: ")
if user.login(email, password):
    print("Login successful.")
else:
    print("Login failed.")

# Change email
if user.logged_in:
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password to change email: ")
    user.change_email(new_email, confirm_password)