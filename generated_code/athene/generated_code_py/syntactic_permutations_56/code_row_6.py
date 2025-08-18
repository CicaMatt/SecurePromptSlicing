from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, input_password):
        if input_password == self.password:
            self.logged_in = True
            print(f"{self.username} logged in successfully.")
        else:
            print("Incorrect password.")

    def change_email(self):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass("Enter your password to confirm the email change: ")

        if old_email != self.email:
            print("The entered current email does not match your existing email.")
            return

        if new_email == self.email:
            print("New email must be different from the current email.")
            return

        if confirm_password != self.password:
            print("Incorrect password. Email change failed.")
            return

        self.email = new_email
        print(f"Email changed successfully to {self.email}")

# Example usage
user = User("john_doe", "john@example.com", "securepassword123")
user.login(input("Enter your password to log in: "))
user.change_email()