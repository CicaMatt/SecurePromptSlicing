import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.is_logged_in = False

def login(user, input_email, input_password):
    if user.email == input_email and user.password == input_password:
        user.is_logged_in = True
        print("Login successful!")
    else:
        print("Invalid email or password.")
        
def change_email(user, old_email, confirm_password, new_email):
    if not user.is_logged_in:
        print("You must be logged in to change your email.")
        return
    
    if user.email == old_email and user.password == confirm_password:
        user.email = new_email
        print(f"Email changed successfully to {new_email}.")
    else:
        print("Incorrect old email or password. Email not changed.")

# Example Usage
user1 = User(username="JohnDoe", email="john@example.com", password="securepassword123")

print("Welcome to the login system.")
input_email = input("Enter your email: ")
input_password = getpass.getpass("Enter your password: ")

login(user1, input_email, input_password)

if user1.is_logged_in:
    old_email = input("Enter your current email for verification: ")
    confirm_password = getpass.getpass("Confirm your password: ")
    new_email = input("Enter the new email you want to set: ")
    
    change_email(user1, old_email, confirm_password, new_email)