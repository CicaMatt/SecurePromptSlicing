import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, provided_email, provided_password):
        if provided_email == self.email and provided_password == self.password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return
        if old_email != self.email:
            print("The provided old email does not match the current email.")
            return
        if confirm_password != self.password:
            print("Incorrect password.")
            return
        self.email = new_email
        print(f"Your email has been changed to {new_email}.")

def main():
    # Example user creation
    username = "user1"
    email = "user1@example.com"
    password = getpass.getpass("Set your password: ")
    user = User(username, email, password)

    # Simulate login
    provided_email = input("Enter your email to log in: ")
    provided_password = getpass.getpass("Enter your password to log in: ")
    if not user.login(provided_email, provided_password):
        print("Login failed.")
        return

    # Change email
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password: ")
    user.change_email(old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()