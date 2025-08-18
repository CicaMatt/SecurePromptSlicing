import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            return True
        else:
            return False

def main():
    # Example user creation
    user = User("example_user", "oldemail@example.com", "securepassword123")

    print("Login to change your email.")
    username_input = input("Enter your username: ")
    password_input = getpass.getpass("Enter your password: ")

    if username_input == user.username and password_input == user.password:
        print("Logged in successfully.")
        old_email_input = input("Enter your current email: ")
        new_email_input = input("Enter your new email: ")
        confirm_password_input = getpass.getpass("Confirm your password: ")

        if user.change_email(old_email_input, new_email_input, confirm_password_input):
            print("Email changed successfully.")
        else:
            print("Failed to change email. Incorrect old email or password.")
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()