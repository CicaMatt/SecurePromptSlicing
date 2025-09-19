import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, confirm_password, new_email):
        if self.email != old_email or self.password != confirm_password:
            print("Incorrect old email or password.")
            return False
        self.email = new_email
        print(f"Email successfully changed to {new_email}.")
        return True

def main():
    # Simulate a logged-in user
    current_user = User(username="john_doe", email="john@example.com", password="securepassword123")

    old_email = input("Enter your current email: ")
    confirm_password = getpass.getpass("Confirm your password: ")
    new_email = input("Enter your new email: ")

    if current_user.change_email(old_email, confirm_password, new_email):
        print("Login and email change successful.")

if __name__ == "__main__":
    main()