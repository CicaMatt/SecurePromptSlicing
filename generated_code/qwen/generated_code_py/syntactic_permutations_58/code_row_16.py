def login_system():
    stored_email = "user@example.com"
    stored_password = "password123"

    print("Enter your old email:")
    old_email = input().strip()
    print("Enter your password:")
    password = input().strip()

    if old_email == stored_email and password == stored_password:
        print("Enter your new email:")
        new_email = input().strip()
        stored_email = new_email
        print("Email updated successfully.")
    else:
        print("Incorrect old email or password. Email not changed.")

if __name__ == "__main__":
    login_system()