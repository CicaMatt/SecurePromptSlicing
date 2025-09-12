import getpass

class SimpleLoginSystem:
    def __init__(self):
        self.username = "user123"
        self.password = "password123"
        self.email = "user@example.com"
        self.logged_in = False

    def login(self):
        input_username = input("Enter your username: ")
        input_password = getpass.getpass("Enter your password: ")
        if input_username == self.username and input_password == self.password:
            self.logged_in = True
            print("Login successful!")
        else:
            print("Invalid username or password. Login failed.")

    def change_email(self):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        old_email = input("Enter your old email: ")
        password_confirmation = getpass.getpass("Confirm your password: ")

        if old_email == self.email and password_confirmation == self.password:
            new_email = input("Enter your new email: ")
            self.email = new_email
            print("Email changed successfully!")
        else:
            print("Incorrect old email or password. Email change failed.")

def main():
    system = SimpleLoginSystem()
    system.login()
    if system.logged_in:
        system.change_email()

if __name__ == "__main__":
    main()