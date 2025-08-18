from getpass import getpass

# Mock database for demonstration purposes
users_db = {
    "john.doe@example.com": {"password": "123456"},
}

def change_email():
    old_email = input("Enter your current email: ")
    if old_email not in users_db:
        print("This email does not exist.")
        return
    
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password: ")

    user_info = users_db[old_email]
    if confirm_password != user_info["password"]:
        print("Incorrect password.")
        return

    # Update the user's email
    users_db[new_email] = users_db.pop(old_email)
    print(f"Email successfully changed to {new_email}.")

# Example usage
change_email()