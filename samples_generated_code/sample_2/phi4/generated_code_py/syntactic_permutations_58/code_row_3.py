import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

    def login(self):
        entered_password = getpass.getpass(f"Password for {self.username}: ")
        if entered_password == self.password:
            self.logged_in = True
            print("Login successful!")
        else:
            print("Incorrect password.")

    def change_email(self, old_email, new_email):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return

        confirmed_password = getpass.getpass("Confirm your password: ")
        if confirmed_password != self.password:
            print("Incorrect password. Email not changed.")
            return

        if old_email == self.email:
            self.email = new_email
            print(f"Email changed from {old_email} to {new_email}.")
        else:
            print("Old email does not match current email. Email not changed.")

def main():
    user = User(username="john_doe", email="john@example.com", password="securepassword123")

    while True:
        action = input("Choose an action: login, change_email, or quit: ")
        
        if action == "login":
            user.login()
        
        elif action == "change_email":
            old_email = input("Enter your current email: ")
            new_email = input("Enter your new email: ")
            user.change_email(old_email, new_email)
        
        elif action == "quit":
            break

        else:
            print("Invalid action. Please try again.")

if __name__ == "__main__":
    main()