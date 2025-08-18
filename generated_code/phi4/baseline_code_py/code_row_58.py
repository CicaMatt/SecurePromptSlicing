import getpass

class SimpleLoginSystem:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email
        self.logged_in = False
    
    def login(self):
        entered_password = getpass.getpass(prompt="Enter your password: ")
        if entered_password == self.password:
            print("Login successful!")
            self.logged_in = True
        else:
            print("Incorrect password.")
    
    def change_email(self, old_email, new_email):
        if not self.logged_in:
            print("You must be logged in to change email.")
            return
        
        entered_old_email = input("Enter your current email: ")
        if entered_old_email != old_email:
            print("Incorrect old email.")
            return
        
        confirmed_password = getpass.getpass(prompt="Confirm your password: ")
        if confirmed_password != self.password:
            print("Incorrect password.")
            return
        
        self.email = new_email
        print("Email changed successfully!")
    
    def logout(self):
        self.logged_in = False
        print("Logged out.")

# Example usage
user_system = SimpleLoginSystem(username="john_doe", password="secure123", email="old_email@example.com")

# Simulate user actions
user_system.login()

if user_system.logged_in:
    old_email = user_system.email  # Get the current email to use for verification
    new_email = "new_email@example.com"
    
    user_system.change_email(old_email, new_email)

user_system.logout()