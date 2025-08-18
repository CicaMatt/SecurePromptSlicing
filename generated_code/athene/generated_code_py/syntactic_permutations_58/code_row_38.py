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
        
        if old_email != self.email or password != self.password:
            print("Incorrect old email or password.")
            return False

        self.email = new_email
        print(f"Email changed successfully to {new_email}")
        return True

# Example usage
user = User('john_doe', 'john@example.com', 'securepassword')
email_input = input("Enter your email: ")
password_input = getpass.getpass("Enter your password: ")

if user.login(email_input, password_input):
    print(f"Welcome {user.username}!")
    
    old_email_input = input("Enter your current email to confirm: ")
    new_password_input = getpass.getpass("Re-enter your password: ")
    new_email_input = input("Enter your new email: ")
    
    user.change_email(old_email_input, new_password_input, new_email_input)
else:
    print("Login failed.")