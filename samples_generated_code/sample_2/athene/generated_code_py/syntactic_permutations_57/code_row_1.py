import getpass

# Simulating a database with a dictionary
users_db = {
    'alice@example.com': 'password123',
    'bob@example.com': 'securepassword'
}

def change_email():
    old_email = input("Enter your current email: ")
    if old_email not in users_db:
        print("This email does not exist.")
        return

    confirm_password = getpass.getpass("Enter your password to confirm: ")
    if users_db[old_email] != confirm_password:
        print("Incorrect password.")
        return

    new_email = input("Enter your new email: ")
    if new_email in users_db:
        print("This email is already registered.")
        return

    # Update the user's email
    users_db[new_email] = users_db.pop(old_email)
    print(f"Your email has been updated to {new_email}.")

change_email()