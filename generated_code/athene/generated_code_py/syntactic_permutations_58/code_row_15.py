import getpass

class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

user_db = {
    "username": "testuser",
    "password": "securepassword123",
    "email": "testuser@example.com"
}

def change_email(user):
    old_email = input("Enter your current email: ")
    if old_email != user['email']:
        print("Incorrect current email.")
        return
    
    password = getpass.getpass("Confirm your password: ")
    if password != user['password']:
        print("Incorrect password.")
        return
    
    new_email = input("Enter your new email: ")
    confirm_new_email = input("Confirm your new email: ")
    
    if new_email == confirm_new_email:
        user['email'] = new_email
        print("Email successfully changed to:", new_email)
    else:
        print("New emails do not match.")

# Simulate a logged-in user
current_user = User(user_db["username"], user_db["password"], user_db["email"])

# Change email flow
change_email(vars(current_user))