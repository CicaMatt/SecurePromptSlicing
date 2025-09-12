import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

def login(user, input_password):
    return user.password == input_password

def change_email(user, old_email, new_email, password):
    if not login(user, password):
        print("Incorrect password.")
        return False
    if user.email != old_email:
        print("Incorrect old email.")
        return False
    user.email = new_email
    print("Email changed successfully.")
    return True

def main():
    # Example user creation
    user = User(username="example_user", password="securepassword123", email="oldemail@example.com")
    
    print("Login to change your email:")
    input_password = getpass.getpass("Enter your password: ")
    
    if not login(user, input_password):
        print("Login failed.")
        return
    
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Confirm your password: ")
    
    change_email(user, old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()