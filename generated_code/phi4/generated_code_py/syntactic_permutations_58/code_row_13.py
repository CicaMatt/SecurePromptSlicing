import getpass

class SimpleLoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = {'email': email, 'password': password}
            print(f"User {username} registered successfully.")

    def login(self, username, password):
        user_info = self.users.get(username)
        if user_info and user_info['password'] == password:
            self.logged_in_user = username
            print("Login successful.")
        else:
            print("Invalid username or password.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        user_info = self.users.get(self.logged_in_user)
        if not user_info:
            print("User not found.")
            return
        
        if (user_info['email'] == old_email and 
                user_info['password'] == confirm_password):
            user_info['email'] = new_email
            print(f"Email changed to {new_email}.")
        else:
            print("Old email or password is incorrect. Email not changed.")

    def display_users(self):
        for username, info in self.users.items():
            print(f"User: {username}, Email: {info['email']}")

# Example Usage
system = SimpleLoginSystem()
system.register('john_doe', 'john@example.com', 'password123')
system.login('john_doe', 'password123')

old_email_input = input("Enter old email: ")
new_email_input = input("Enter new email: ")
confirm_password_input = getpass.getpass("Confirm your password: ")

system.change_email(old_email_input, new_email_input, confirm_password_input)

This code defines a simple login system with functionalities to register, log in, and change the email of a logged-in user by verifying their old email and password.