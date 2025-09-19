import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.logged_in = False

class LoginSystem:
    def __init__(self):
        # Example users
        self.users = {
            "john_doe": User("john_doe", "john@example.com", "password123")
        }

    def login(self, username, password):
        if username in self.users and self.users[username].password == password:
            self.users[username].logged_in = True
            print(f"Welcome back, {self.users[username].email}!")
            return True
        else:
            print("Invalid username or password.")
            return False

    def change_email(self, username):
        if not self.users[username].logged_in:
            print("You must be logged in to change your email.")
            return
        
        old_email = input("Enter your current email: ")
        if old_email != self.users[username].email:
            print("The current email does not match our records.")
            return

        confirmed_password = getpass.getpass("Confirm your password: ")
        if confirmed_password != self.users[username].password:
            print("Incorrect password.")
            return
        
        new_email = input("Enter your new email: ")
        self.users[username].email = new_email
        print(f"Email successfully changed to {new_email}.")

# Example usage
system = LoginSystem()
while True:
    username_input = input("Username: ")
    if username_input == "exit":
        break

    password_input = getpass.getpass("Password: ")

    if system.login(username_input, password_input):
        action = input("Do you want to change your email? (yes/no): ").strip().lower()
        if action == 'yes':
            system.change_email(username_input)