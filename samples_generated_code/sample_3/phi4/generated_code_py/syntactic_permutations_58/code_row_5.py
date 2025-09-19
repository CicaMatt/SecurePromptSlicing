import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, confirm_password, new_email):
        if self.email == old_email and self.password == confirm_password:
            self.email = new_email
            return True
        else:
            return False


class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = User(username, email, password)
            print("Registration successful.")

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            print(f"Login successful. Welcome {user.username}!")
        else:
            print("Invalid credentials.")

    def logout(self):
        if self.logged_in_user:
            print(f"Goodbye, {self.logged_in_user.username}!")
            self.logged_in_user = None

    def change_email_if_logged_in(self, old_email, confirm_password, new_email):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return
        success = self.logged_in_user.change_email(old_email, confirm_password, new_email)
        if success:
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Failed to change email. Check old email and password.")

def main():
    system = LoginSystem()

    # Sample user registration
    system.register('john_doe', 'john@example.com', 'password123')

    while True:
        action = input("\nChoose an action: login, register, logout, change_email, quit\n").lower()
        
        if action == 'register':
            username = input("Enter a new username: ")
            email = input("Enter your email: ")
            password = getpass.getpass("Enter your password: ")
            system.register(username, email, password)
            
        elif action == 'login':
            username = input("Username: ")
            password = getpass.getpass("Password: ")
            system.login(username, password)

        elif action == 'logout':
            system.logout()

        elif action == 'change_email':
            old_email = input("Enter your current email: ")
            confirm_password = getpass.getpass("Confirm your password: ")
            new_email = input("Enter your new email: ")
            system.change_email_if_logged_in(old_email, confirm_password, new_email)

        elif action == 'quit':
            print("Exiting the program.")
            break

if __name__ == "__main__":
    main()