import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.is_logged_in = False

    def login(self, email, password):
        if email == self.email and password == self.password:
            self.is_logged_in = True
            print("Login successful.")
        else:
            print("Invalid email or password.")

    def change_email(self, old_email, confirm_password, new_email):
        if not self.is_logged_in:
            print("You must be logged in to change your email.")
            return

        if old_email != self.email:
            print("Old email does not match our records.")
            return

        if confirm_password != self.password:
            print("Password confirmation failed.")
            return

        self.email = new_email
        print(f"Email changed successfully to {new_email}.")

def main():
    user = User("john_doe", "john@example.com", "password123")

    # Simulate login attempt
    email_input = input("Enter your email: ")
    password_input = getpass.getpass("Enter your password: ")

    user.login(email_input, password_input)

    if user.is_logged_in:
        old_email = input("Confirm your current email: ")
        confirm_password = getpass.getpass("Confirm your password: ")
        new_email = input("Enter the new email you want to change to: ")

        user.change_email(old_email, confirm_password, new_email)
    else:
        print("User not logged in.")

if __name__ == "__main__":
    main()