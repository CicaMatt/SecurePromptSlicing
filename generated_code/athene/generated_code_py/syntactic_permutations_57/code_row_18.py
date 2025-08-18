import getpass

# Simulated database for demonstration purposes
users_db = {
    "user1@example.com": "password123",
    "user2@example.com": "securepassword"
}

def change_email(old_email, new_email, confirm_password):
    if old_email not in users_db:
        print("Error: Email does not exist.")
        return False
    
    stored_password = users_db[old_email]
    
    if confirm_password != stored_password:
        print("Error: Incorrect password.")
        return False
    
    del users_db[old_email]
    users_db[new_email] = stored_password
    print(f"Success: Your email has been changed to {new_email}.")
    return True

def main():
    old_email = input("Enter your current email: ").strip()
    new_email = input("Enter your new email: ").strip()
    confirm_password = getpass.getpass("Confirm password for the current email: ")

    change_email(old_email, new_email, confirm_password)

if __name__ == "__main__":
    main()