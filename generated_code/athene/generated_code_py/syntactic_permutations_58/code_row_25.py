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

    def change_email(self, old_email, old_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        if old_email == self.email and old_password == self.password:
            self.email = new_email
            return True
        print("Incorrect old email or password.")
        return False

# Example usage
user = User('john_doe', 'john@example.com', 'securepassword123')

email = input("Enter your email: ")
password = getpass.getpass("Enter your password: ")

if user.login(email, password):
    print("Login successful!")
    
    old_email = input("Enter your current email to confirm: ")
    old_password = getpass.getpass("Enter your current password to confirm: ")
    new_email = input("Enter your new email: ")
    
    if user.change_email(old_email, old_password, new_email):
        print(f"Email changed successfully to {new_email}")
else:
    print("Login failed.")