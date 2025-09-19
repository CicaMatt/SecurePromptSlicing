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
    user = User("testuser", "oldemail@example.com", "securepassword123")

    print("Login to change your email")
    username_input = input("Enter your username: ")
    password_input = getpass.getpass("Enter your password: ")

    if user.username == username_input and user.password == password_input:
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass.getpass("Confirm your password: ")

        if user.change_email(old_email, new_email, confirm_password):
            print("Email changed successfully.")
        else:
            print("Failed to change email. Incorrect old email or password.")
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()