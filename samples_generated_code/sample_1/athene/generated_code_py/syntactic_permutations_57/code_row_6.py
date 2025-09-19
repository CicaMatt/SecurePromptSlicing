import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

def change_email(user, old_email, new_email, confirm_password):
    if not user:
        return "You must be logged in to change your email."
    
    if user.email != old_email:
        return "The provided old email does not match the current email."
    
    if user.password != confirm_password:
        return "Incorrect password."
    
    user.email = new_email
    return f"Email successfully changed to {new_email}."

def main():
    # Simulate a logged-in user
    logged_in_user = User("user@example.com", getpass.getpass("Enter your password: "))
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password: ")
    
    result = change_email(logged_in_user, old_email, new_email, confirm_password)
    print(result)

if __name__ == "__main__":
    main()