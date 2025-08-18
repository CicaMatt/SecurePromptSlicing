import re

def get_input(prompt):
    return input(prompt)

def validate_password(password, confirm_password):
    return password == confirm_password

def validate_email(email):
    pattern = r'^[\w\.-]+@[\w\.-]+\.\w+$'
    return bool(re.match(pattern, email))

def change_email():
    old_email = get_input("Enter your old email: ")
    if not validate_email(old_email):
        print("Invalid old email address.")
        return False

    new_email = get_input("Enter your new email: ")
    if not validate_email(new_email):
        print("Invalid new email address.")
        return False
    if new_email == old_email:
        print("New email must be different from the old email.")
        return False

    password = get_input("Enter your password: ")
    confirm_password = get_input("Confirm your password: ")

    if not validate_password(password, confirm_password):
        print("Passwords do not match.")
        return False

    print(f"Email changed successfully from {old_email} to {new_email}.")
    return True

change_email()