from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

def change_email(user):
    print(f"Welcome, {user.username}!")
    
    old_email = input("Enter your current email: ")
    if old_email != user.email:
        print("Incorrect current email.")
        return
    
    new_email = input("Enter your new email: ")
    if new_email == user.email:
        print("New email must be different from the current one.")
        return
    
    password = getpass("Confirm your password to proceed: ")
    if password != user.password:
        print("Incorrect password.")
        return
    
    user.email = new_email
    print(f"Your email has been updated successfully. New email: {user.email}")

# Example usage
current_user = User("john_doe", "john@example.com", "securepassword")
change_email(current_user)