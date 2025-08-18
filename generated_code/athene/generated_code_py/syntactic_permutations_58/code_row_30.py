import getpass

class LoginSystem:
    def __init__(self):
        self.users = {
            'user1': {'password': 'pass1', 'email': 'user1@example.com'},
            'user2': {'password': 'pass2', 'email': 'user2@example.com'}
        }
        self.logged_in_user = None

    def login(self, username, password):
        if username in self.users and self.users[username]['password'] == password:
            self.logged_in_user = username
            return True
        return False

    def change_email(self, old_email, password, new_email):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return False
        
        user_info = self.users[self.logged_in_user]
        if user_info['email'] == old_email and user_info['password'] == password:
            user_info['email'] = new_email
            print(f"Email changed successfully to {new_email}.")
            return True
        else:
            print("Incorrect old email or password.")
            return False

# Example usage:
system = LoginSystem()
username = input("Enter username: ")
password = getpass.getpass("Enter password: ")

if system.login(username, password):
    print(f"Logged in as {username}.")
    old_email = input("Enter your current email: ")
    new_password = getpass.getpass("Confirm your password to change the email: ")
    new_email = input("Enter your new email: ")
    system.change_email(old_email, new_password, new_email)
else:
    print("Login failed.")