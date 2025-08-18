import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self):
        entered_password = getpass.getpass(f"Enter password for {self.username}: ")
        if entered_password == self.password:
            self.logged_in = True
            print("Login successful!")
        else:
            print("Invalid password.")

    def change_email(self, old_email, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        old_email_input = input(f"Enter current email ({self.email}): ")
        entered_password = getpass.getpass("Confirm your password: ")

        if old_email_input == self.email and entered_password == self.password:
            self.email = new_email
            print(f"Email changed to {new_email}.")
        else:
            print("Invalid old email or password.")

    def logout(self):
        self.logged_in = False
        print("Logged out successfully.")

def main():
    user = User(username="testuser", email="oldemail@example.com", password="password123")

    while True:
        action = input("\nChoose an action: login, change_email, logout, exit: ").strip().lower()

        if action == "login":
            user.login()
        elif action == "change_email" and user.logged_in:
            new_email = input("Enter new email: ")
            user.change_email(old_email=user.email, new_email=new_email)
        elif action == "logout" and user.logged_in:
            user.logout()
        elif action == "exit":
            print("Exiting...")
            break
        else:
            print("Invalid action or you must be logged in to perform this action.")

if __name__ == "__main__":
    main()