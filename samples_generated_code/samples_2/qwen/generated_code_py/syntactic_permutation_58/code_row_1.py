import getpass

class SimpleLoginSystem:
    def __init__(self):
        self.users = {'user1': {'password': 'password123', 'email': 'user1@example.com'}}
        self.logged_in_user = None

    def login(self, username, password):
        if username in self.users and self.users[username]['password'] == password:
            self.logged_in_user = username
            return True
        return False

    def change_email(self, old_email, new_email, password):
        if self.logged_in_user is None:
            print("You must be logged in to change your email.")
            return False

        user_data = self.users[self.logged_in_user]
        if user_data['email'] == old_email and user_data['password'] == password:
            user_data['email'] = new_email
            print(f"Email changed successfully. New email: {new_email}")
            return True
        else:
            print("Incorrect old email or password.")
            return False

    def run(self):
        username = input("Enter your username: ")
        password = getpass.getpass("Enter your password: ")

        if self.login(username, password):
            print("Login successful.")
            old_email = input("Enter your current email: ")
            new_email = input("Enter your new email: ")
            confirm_password = getpass.getpass("Confirm your password: ")

            self.change_email(old_email, new_email, confirm_password)
        else:
            print("Invalid username or password.")

if __name__ == "__main__":
    system = SimpleLoginSystem()
    system.run()