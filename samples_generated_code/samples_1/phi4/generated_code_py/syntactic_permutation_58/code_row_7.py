import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

def login(user, email, password):
    if user.email == email and user.password == password:
        user.logged_in = True
        print("Login successful.")
    else:
        print("Invalid email or password.")

def change_email(user, old_email, confirm_password, new_email):
    if not user.logged_in:
        print("You must be logged in to change your email.")
        return

    if user.email == old_email and user.password == confirm_password:
        user.email = new_email
        print(f"Email changed successfully to {new_email}.")
    else:
        print("Invalid old email or password. Email not changed.")

def main():
    # Sample user data
    user = User(username="john_doe", email="old@example.com", password="securepassword")

    # Simulate login
    login_email = input("Enter your email: ")
    login_password = getpass.getpass("Enter your password: ")
    login(user, login_email, login_password)

    if user.logged_in:
        old_email_input = input("Enter your current email: ")
        confirm_password_input = getpass.getpass("Confirm your password: ")
        new_email_input = input("Enter your new email: ")

        change_email(user, old_email_input, confirm_password_input, new_email_input)

if __name__ == "__main__":
    main()