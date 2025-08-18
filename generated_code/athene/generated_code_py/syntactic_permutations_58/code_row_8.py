import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self, email, password):
        if self.email == email and self.password == password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        if self.email != old_email or self.password != password:
            print("Incorrect old email or password.")
            return False
        self.email = new_email
        print(f"Email changed successfully to {new_email}.")
        return True

def main():
    # Example user creation
    user = User('john_doe', 'john@example.com', 'securepassword123')

    # Simulate login
    email = input("Enter your email: ")
    password = getpass.getpass("Enter your password: ")
    if not user.login(email, password):
        print("Login failed.")
        return

    # Change email flow
    old_email = input("Enter your current email: ")
    password = getpass.getpass("Confirm your password: ")
    new_email = input("Enter your new email: ")
    user.change_email(old_email, password, new_email)

if __name__ == "__main__":
    main()