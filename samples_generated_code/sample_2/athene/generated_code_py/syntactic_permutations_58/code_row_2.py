import getpass

users = {
    "john.doe@example.com": "password123",
}

def login(email, password):
    if email in users and users[email] == password:
        return True
    return False

def change_email(current_email, current_password, new_email):
    if not login(current_email, current_password):
        print("Incorrect email or password.")
        return
    users[new_email] = users.pop(current_email)
    print(f"Email changed to: {new_email}")

current_email = input("Enter your current email: ")
current_password = getpass.getpass("Enter your current password: ")
new_email = input("Enter your new email: ")

change_email(current_email, current_password, new_email)