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

    def change_email(self, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        
        old_password = getpass.getpass(prompt="Enter your current password: ")
        if old_password != self.password:
            print("Incorrect password. Email change failed.")
            return False
        
        self.email = new_email
        print(f"Email successfully changed to {self.email}")
        return True

# Example usage:
user = User('john_doe', 'john@example.com', 'securepassword')
if user.login(input("Enter email: "), getpass.getpass(prompt="Enter password: ")):
    user.change_email(input("Enter new email: "))