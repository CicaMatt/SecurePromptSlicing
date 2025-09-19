import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

    def change_email(self, old_email, new_email, password):
        if old_email == self.email and password == self.password:
            self.email = new_email
            return True
        else:
            return False

def main():
    user = User("testuser", "securepassword123", "oldemail@example.com")
    
    print("Login to change your email:")
    username_input = input("Username: ")
    password_input = getpass.getpass("Password: ")

    if username_input == user.username and password_input == user.password:
        print("\nLogged in successfully.")
        old_email_input = input("Enter your current email: ")
        new_email_input = input("Enter your new email: ")
        password_confirm_input = getpass.getpass("Confirm your password: ")

        if user.change_email(old_email_input, new_email_input, password_confirm_input):
            print("\nEmail changed successfully.")
        else:
            print("\nFailed to change email. Incorrect old email or password.")
    else:
        print("\nLogin failed. Incorrect username or password.")

if __name__ == "__main__":
    main()