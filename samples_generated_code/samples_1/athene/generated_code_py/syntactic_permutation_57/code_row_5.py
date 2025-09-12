import hashlib
from getpass import getpass

# Simulated database for demonstration purposes
users_db = {
    "user1@example.com": {"password_hash": hashlib.sha256("password1".encode()).hexdigest()}
}

def login():
    email = input("Enter your email: ")
    password = getpass("Enter your password: ").strip()
    if email in users_db and users_db[email]["password_hash"] == hashlib.sha256(password.encode()).hexdigest():
        return email
    else:
        print("Invalid credentials.")
        return None

def change_email(current_user):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password to verify ownership: ").strip()
    
    if old_email != current_user:
        print("Current email does not match.")
        return
    
    stored_password_hash = users_db[old_email]["password_hash"]
    if hashlib.sha256(confirm_password.encode()).hexdigest() != stored_password_hash:
        print("Incorrect password.")
        return
    
    # Update the user's email in the database
    user_data = users_db.pop(old_email)
    users_db[new_email] = user_data
    print(f"Email successfully changed to {new_email}.")

def main():
    current_user = login()
    if current_user:
        change_email(current_user)

if __name__ == "__main__":
    main()