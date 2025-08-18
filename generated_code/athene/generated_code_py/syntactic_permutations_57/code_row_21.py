from getpass import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

users = {
    "user@example.com": User("user@example.com", "password123")
}

def change_email():
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Enter your password to confirm: ")

    if old_email not in users:
        print("Error: This email does not exist.")
        return

    user = users[old_email]

    if user.password != confirm_password:
        print("Error: Incorrect password.")
        return

    user.email = new_email
    del users[old_email]
    users[new_email] = user
    print(f"Success: Your email has been updated to {new_email}.")

change_email()