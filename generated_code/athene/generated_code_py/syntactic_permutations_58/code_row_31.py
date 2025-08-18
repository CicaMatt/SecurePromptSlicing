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
            return True
        return False

    def change_email(self, old_email, input_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        if old_email != self.email or input_password != self.password:
            print("Incorrect old email or password.")
            return False
        self.email = new_email
        print(f"Email changed successfully to {new_email}")
        return True

# Example usage
user = User('john_doe', 'john@example.com', 'securepassword')
input_email = input("Enter your email: ")
input_password = getpass.getpass("Enter your password: ")

if user.login(input_email, input_password):
    print("Login successful.")
    old_email = input("Enter your current email to confirm: ")
    new_password = getpass.getpass("Enter your password again: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, new_password, new_email)
else:
    print("Login failed.")