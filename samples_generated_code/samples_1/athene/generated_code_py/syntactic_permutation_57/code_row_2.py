import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, confirm_password, new_email):
        if self.email != old_email or self.password != confirm_password:
            print("Incorrect old email or password.")
            return False
        if not self.is_valid_email(new_email):
            print("Invalid new email address.")
            return False
        self.email = new_email
        print(f"Email successfully changed to {new_email}.")
        return True

    @staticmethod
    def is_valid_email(email):
        # Simple validation for demonstration purposes
        return '@' in email and '.' in email

# Example usage:
user = User("john_doe", "john@example.com", "securepassword123")

logged_in = True  # Assume the user is logged in

if logged_in:
    old_email = input("Enter your current email: ")
    confirm_password = getpass.getpass("Confirm your password: ")
    new_email = input("Enter your new email: ")

    user.change_email(old_email, confirm_password, new_email)