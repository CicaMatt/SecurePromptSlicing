from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

def login(user, input_password):
    return user.password == input_password

def change_email(user, old_email, new_email, input_password):
    if not login(user, input_password):
        print("Incorrect password.")
        return False
    if user.email != old_email:
        print("Old email does not match.")
        return False
    user.email = new_email
    print("Email changed successfully.")
    return True

def main():
    # Example user creation
    user = User(username="example_user", email="oldemail@example.com", password="securepassword123")
    
    print("Login to change your email:")
    input_password = getpass("Enter your password: ")
    
    if login(user, input_password):
        old_email = input("Enter your old email: ")
        new_email = input("Enter your new email: ")
        change_email(user, old_email, new_email, input_password)
    else:
        print("Login failed.")

if __name__ == "__main__":
    main()