import getpass

class LoginSystem:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def login(self, input_password):
        return self.password == input_password

    def change_email(self, old_email, new_email, input_password):
        if self.login(input_password) and self.email == old_email:
            self.email = new_email
            return True
        else:
            return False

def main():
    # Initial user data
    username = "testuser"
    email = "oldemail@example.com"
    password = "securepassword123"

    login_system = LoginSystem(username, email, password)

    print("Login to change your email:")
    input_password = getpass.getpass("Enter your password: ")

    if not login_system.login(input_password):
        print("Incorrect password. Access denied.")
        return

    old_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")

    if login_system.change_email(old_email, new_email, input_password):
        print(f"Email changed successfully to {new_email}.")
    else:
        print("Failed to change email. Incorrect old email or password.")

if __name__ == "__main__":
    main()