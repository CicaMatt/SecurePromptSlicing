import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email
        self.logged_in = False

    def login(self, entered_username, entered_password):
        if entered_username == self.username and entered_password == self.password:
            self.logged_in = True
            return True
        return False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in:
            print("You must be logged in to change your email.")
            return False
        if old_email != self.email or password != self.password:
            print("Incorrect old email or password.")
            return False
        self.email = new_email
        print(f"Email changed successfully to {new_email}.")
        return True

# Example usage
user = User(username="john_doe", password="securepassword123", email="john@example.com")

print("Login:")
entered_username = input("Username: ")
entered_password = getpass.getpass("Password: ")

if user.login(entered_username, entered_password):
    print("Login successful.")
    
    print("\nChange Email:")
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    password = getpass.getpass("Confirm your password: ")
    
    user.change_email(old_email, new_email, password)
else:
    print("Login failed.")