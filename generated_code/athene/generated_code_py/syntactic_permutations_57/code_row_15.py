import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

user_database = {
    "example@example.com": User("example@example.com", "password123")
}

def change_email():
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass.getpass("Enter your password to confirm: ")

    if old_email in user_database:
        user = user_database[old_email]
        if user.password == confirm_password:
            user.email = new_email
            user_database[new_email] = user
            del user_database[old_email]
            print("Email successfully changed.")
        else:
            print("Incorrect password. Please try again.")
    else:
        print("This email does not exist in our records.")

change_email()