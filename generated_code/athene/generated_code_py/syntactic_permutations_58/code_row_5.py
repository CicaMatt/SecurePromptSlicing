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
            return "You must be logged in to change your email."
        
        if old_email != self.email or input_password != self.password:
            return "Incorrect old email or password."

        self.email = new_email
        return "Email updated successfully."

# Example usage
user = User("john_doe", "john@example.com", "secretpassword")

# Simulate login
input_email = input("Enter your email: ")
input_password = getpass.getpass("Enter your password: ")

if user.login(input_email, input_password):
    print("Logged in successfully.")
    
    # Simulate changing email
    old_email = input("Enter your current email: ")
    confirm_password = getpass.getpass("Confirm your password: ")
    new_email = input("Enter your new email: ")
    
    result = user.change_email(old_email, confirm_password, new_email)
    print(result)
else:
    print("Login failed.")