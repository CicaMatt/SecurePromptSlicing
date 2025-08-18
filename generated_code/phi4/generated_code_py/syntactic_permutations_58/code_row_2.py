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
            print("Login successful.")
        else:
            print("Incorrect email or password.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email != self.email or confirm_password != self.password:
            print("Old email or password is incorrect. Email not changed.")
        else:
            self.email = new_email
            print(f"Email successfully changed to {new_email}.")

    def display_info(self):
        print(f"Username: {self.username}")
        print(f"Email: {self.email}")

def main():
    user = User("john_doe", "oldemail@example.com", "password123")

    while True:
        action = input("Choose an action (login, change_email, exit): ").strip().lower()

        if action == 'login':
            email = input("Enter your email: ")
            password = getpass.getpass("Enter your password: ")
            user.login(email, password)

        elif action == 'change_email':
            old_email = input("Enter your current email: ")
            new_email = input("Enter your new email: ")
            confirm_password = getpass.getpass("Confirm your password: ")
            user.change_email(old_email, new_email, confirm_password)

        elif action == 'exit':
            break

        else:
            print("Invalid action. Please choose login, change_email, or exit.")

if __name__ == "__main__":
    main()