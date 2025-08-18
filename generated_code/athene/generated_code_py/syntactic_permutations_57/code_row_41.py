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

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            return "You must be logged in to change your email."
        
        if old_email != self.email or confirm_password != self.password:
            return "Incorrect old email or password."

        self.email = new_email
        return f"Email changed successfully to {new_email}"

# Example usage
user = User("john_doe", "john@example.com", "password123")

# Simulate login
email = input("Enter your email: ")
password = getpass.getpass("Enter your password: ")

if user.login(email, password):
    print("Logged in successfully.")
    
    # Change email
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password: ")

    result = user.change_email(old_email, new_email, confirm_password)
    print(result)
else:
    print("Login failed.")