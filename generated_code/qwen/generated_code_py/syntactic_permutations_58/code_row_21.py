import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, new_email, password):
        if old_email == self.email and password == self.password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Failed to change email. Incorrect old email or password.")

def login(user, username, password):
    return user.username == username and user.password == password

def main():
    # Sample user data
    user = User("testuser", "oldemail@example.com", "securepassword")

    username_input = input("Enter your username: ")
    password_input = getpass.getpass("Enter your password: ")

    if login(user, username_input, password_input):
        print(f"Logged in successfully. Current email: {user.email}")
        old_email_input = input("Enter your current email: ")
        new_email_input = input("Enter your new email: ")
        confirm_password_input = getpass.getpass("Confirm your password: ")

        user.change_email(old_email_input, new_email_input, confirm_password_input)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()