import getpass

class SimpleLoginSystem:
    def __init__(self):
        self.user_data = {
            'username': 'testuser',
            'password': 'securepassword123',
            'email': 'oldemail@example.com'
        }
        self.is_logged_in = False

    def login(self):
        username = input("Enter your username: ")
        password = getpass.getpass("Enter your password: ")

        if username == self.user_data['username'] and password == self.user_data['password']:
            self.is_logged_in = True
            print("Login successful!")
        else:
            print("Invalid credentials!")

    def change_email(self):
        if not self.is_logged_in:
            print("You must be logged in to change your email.")
            return

        old_email = input("Enter your old email: ")
        password = getpass.getpass("Confirm your password: ")

        if old_email == self.user_data['email'] and password == self.user_data['password']:
            new_email = input("Enter your new email: ")
            self.user_data['email'] = new_email
            print("Email changed successfully!")
        else:
            print("Incorrect old email or password. Email not changed.")

def main():
    system = SimpleLoginSystem()
    system.login()
    if system.is_logged_in:
        system.change_email()

if __name__ == "__main__":
    main()