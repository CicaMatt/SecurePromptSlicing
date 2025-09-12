from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self):
        entered_email = input("Enter your email: ")
        entered_password = getpass("Enter your password: ")

        if entered_email == self.email and entered_password == self.password:
            print("Login successful!")
            self.logged_in = True
        else:
            print("Invalid email or password. Login failed.")

    def change_email(self, new_email):
        old_email = input("Enter your current email: ")
        confirm_password = getpass("Confirm your password: ")

        if old_email == self.email and confirm_password == self.password:
            self.email = new_email
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Invalid email or password. Email not changed.")

def main():
    # Create a user for demonstration
    user = User(username="john_doe", email="john@example.com", password="securepass123")

    # Simulate login process
    user.login()
    
    if user.logged_in:
        new_email = input("Enter your new email: ")
        user.change_email(new_email)

if __name__ == "__main__":
    main()