from getpass import getpass

class LoginPage:
    def __init__(self):
        self.users = {
            "user@example.com": "password123"
        }

    def login(self, email, password):
        if email in self.users and self.users[email] == password:
            return True
        return False

    def change_email(self):
        old_email = input("Enter your old email: ")
        current_password = getpass("Enter your current password: ")

        if not self.login(old_email, current_password):
            print("Incorrect email or password.")
            return

        new_email = input("Enter your new email: ")
        confirm_password = getpass("Confirm your password: ")

        if confirm_password != current_password:
            print("Passwords do not match.")
            return

        if old_email == new_email:
            print("New email must be different from the old email.")
            return

        self.users[new_email] = self.users.pop(old_email)
        print("Email successfully changed.")

login_page = LoginPage()
login_page.change_email()