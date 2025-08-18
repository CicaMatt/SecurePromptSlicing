import getpass

class LoginSystem:
    def __init__(self, username, password, email):
        self.logged_in = False
        self.username = username
        self.password = password
        self.email = email

    def login(self):
        entered_username = input("Enter your username: ")
        entered_password = getpass.getpass("Enter your password: ")

        if entered_username == self.username and entered_password == self.password:
            self.logged_in = True
            print("Login successful.")
        else:
            print("Incorrect username or password.")

    def change_email(self):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        old_email = input("Enter your old email: ")
        confirm_password = getpass.getpass("Confirm your password: ")

        if old_email == self.email and confirm_password == self.password:
            new_email = input("Enter your new email: ")
            self.email = new_email
            print(f"Email changed to {self.email}.")
        else:
            print("Incorrect old email or password. Email not changed.")

# Example usage:
user_system = LoginSystem(username="test_user", password="password123", email="old@example.com")

while True:
    action = input("Do you want to login, change email, or exit? (login/change/exit): ").lower()
    
    if action == "login":
        user_system.login()
    elif action == "change":
        user_system.change_email()
    elif action == "exit":
        break
    else:
        print("Invalid option. Please choose 'login', 'change', or 'exit'.")