class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, password):
        if self.is_authenticated(old_email, password):
            self.email = new_email
            return True
        else:
            return False

    def is_authenticated(self, email, password):
        return self.email == email and self.password == password


def main():
    # Example user creation
    user = User(username="john_doe", email="john@example.com", password="securepassword123")

    # Simulate login and email change
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    password = input("Enter your password to confirm: ")

    if user.change_email(old_email, new_email, password):
        print("Email changed successfully.")
    else:
        print("Failed to change email. Incorrect old email or password.")


if __name__ == "__main__":
    main()