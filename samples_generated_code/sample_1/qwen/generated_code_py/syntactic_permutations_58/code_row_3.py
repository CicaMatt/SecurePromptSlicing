from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.is_logged_in = False

    def login(self, password):
        if password == self.password:
            self.is_logged_in = True
            print("Login successful.")
        else:
            print("Incorrect password. Login failed.")

    def change_email(self, old_email, new_email, password):
        if not self.is_logged_in:
            print("You must be logged in to change your email.")
            return
        if self.email != old_email:
            print("The old email does not match the current email.")
            return
        if password != self.password:
            print("Incorrect password. Email change failed.")
            return
        self.email = new_email
        print(f"Email changed successfully to {self.email}.")

def main():
    user = User(username="testuser", email="oldemail@example.com", password="securepassword")
    
    print("Login to your account:")
    password = getpass("Enter your password: ")
    user.login(password)
    
    if user.is_logged_in:
        print("\nChange Email:")
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass("Confirm your password: ")
        user.change_email(old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()