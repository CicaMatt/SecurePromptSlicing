import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, confirm_password):
        if self.email != old_email:
            print("The provided old email does not match the existing email.")
            return False
        if confirm_password != self.password:
            print("Incorrect password.")
            return False
        self.email = new_email
        print(f"Email successfully changed to {new_email}.")
        return True

# Example usage
user = User('example@example.com', 'password123')

old_email = input("Enter your current email: ")
new_email = input("Enter your new email: ")
confirm_password = getpass.getpass("Confirm your password: ")

user.change_email(old_email, new_email, confirm_password)