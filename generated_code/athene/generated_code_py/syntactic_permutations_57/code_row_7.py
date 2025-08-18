import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

def change_email(user):
    old_email = input("Enter your current email: ").strip()
    if old_email != user.email:
        print("Incorrect email.")
        return
    
    new_email = input("Enter your new email: ").strip()
    confirm_password = getpass.getpass("Confirm your password to verify ownership: ")

    if confirm_password != user.password:
        print("Incorrect password.")
        return

    user.email = new_email
    print("Email successfully changed.")

# Example usage
if __name__ == "__main__":
    # Simulate a logged-in user
    current_user = User(email="example@example.com", password="securepassword")

    change_email(current_user)