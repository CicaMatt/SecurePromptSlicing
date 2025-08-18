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
            print("Login successful.")
            return True
        else:
            print("Incorrect email or password.")
            return False

    def change_email(self, old_email, password, new_email):
        if self.logged_in and old_email == self.email and password == self.password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Failed to change email. Incorrect old email or password.")

# Example usage
user = User('john_doe', 'john@example.com', 's3cur3p455w0rd')
input_email = input("Enter your email: ")
input_password = getpass.getpass("Enter your password: ")

if user.login(input_email, input_password):
    old_email = input("Enter your current email to confirm: ")
    password = getpass.getpass("Re-enter your password to confirm: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, password, new_email)