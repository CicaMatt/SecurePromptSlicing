import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

def login(user, entered_password):
    return user.password == entered_password

def change_email(user, old_email, new_email, entered_password):
    if not login(user, entered_password):
        print("Incorrect password.")
        return False
    if user.email != old_email:
        print("Old email does not match.")
        return False
    user.email = new_email
    print("Email changed successfully.")
    return True

def main():
    # Example user
    user = User(username="example_user", password="securepassword123", email="oldemail@example.com")
    
    print("Login to change your email.")
    entered_password = getpass.getpass("Enter your password: ")
    
    if not login(user, entered_password):
        print("Login failed.")
        return
    
    old_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")
    
    change_email(user, old_email, new_email, entered_password)

if __name__ == "__main__":
    main()