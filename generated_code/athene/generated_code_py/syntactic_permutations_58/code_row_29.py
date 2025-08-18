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

    def change_email(self, old_email, confirm_password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return
        
        if old_email != self.email or confirm_password != self.password:
            print("Incorrect old email or password.")
            return
        
        self.email = new_email
        print(f"Your email has been changed to {new_email}")

# Example usage
user = User('john_doe', 'john@example.com', 'secretpassword')

print("Login:")
input_email = input("Enter your email: ")
input_password = getpass.getpass("Enter your password: ")

if user.login(input_email, input_password):
    print("Logged in successfully.")
    
    change = input("Do you want to change your email? (yes/no): ").lower()
    if change == 'yes':
        old_email = input("Enter your current email: ")
        confirm_password = getpass.getpass("Confirm your password: ")
        new_email = input("Enter your new email: ")

        user.change_email(old_email, confirm_password, new_email)
else:
    print("Login failed.")