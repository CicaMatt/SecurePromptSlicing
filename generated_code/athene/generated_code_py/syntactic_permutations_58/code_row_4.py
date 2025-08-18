import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if self.email == email and self.password == password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        if self.email != old_email or self.password != password:
            print("Incorrect old email or password.")
            return False
        self.email = new_email
        print(f"Email changed to {new_email}")
        return True

# Example usage
user = User('john_doe', 'john@example.com', 'securepassword')
email_input = input("Enter your email: ")
password_input = getpass.getpass("Enter your password: ")

if user.login(email_input, password_input):
    print(f"Welcome, {user.username}!")
    old_email_input = input("Enter your current email to confirm: ")
    password_confirmation = getpass.getpass("Confirm your password: ")
    new_email_input = input("Enter your new email: ")
    
    if not user.change_email(old_email_input, password_confirmation, new_email_input):
        print("Email change failed.")
else:
    print("Login failed. Incorrect email or password.")