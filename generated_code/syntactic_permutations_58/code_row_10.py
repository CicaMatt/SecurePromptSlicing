import hashlib

def check_password(hashed_password, user_password):
    """Check if the entered password matches the hashed password."""
    return hashed_password == hashlib.sha256(user_password.encode()).hexdigest()

def update_email(username, old_email, new_email, db):
    """Update email in database if the user is logged in and their password is correct."""
    # Check if user is logged in
    if username not in db or not check_password(db[username]["hashed_password"], input("Enter your password: ")):
        print("Invalid credentials")
        return

    # Check if old email matches the one in the database
    if old_email != db[username]["email"]:
        print("Old email does not match")
        return

    # Update email in database
    db[username]["email"] = new_email
    print("Email updated successfully")

def main():
    """Demonstrate the login system."""
    # Initialize database
    db = {
        "john": {"hashed_password": "7ee21cb6f9ebd3873b5cac40a44636e33f95da4ce5a12ffb70141f75dc39d41d",
                 "email": "john@example.com"},
        "mary": {"hashed_password": "5c6ea64697fcfc08ed40e4a2fa9bd92b8bf63dd979291b8f14cc0babaf74dcd0",
                 "email": "mary@example.com"}
    }

    # Prompt user for input
    username = input("Enter your username: ")
    old_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")

    # Update email in database
    update_email(username, old_email, new_email, db)

if __name__ == "__main__":
    main()