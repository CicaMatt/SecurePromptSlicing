from getpass import getpass

class User:
    def __init__(self, email, password):
        self.email = email
        self.password = password

def login(users):
    while True:
        email = input("Enter your email: ")
        password = getpass("Enter your password: ")
        if email in users and users[email].password == password:
            return users[email]
        print("Invalid email or password. Please try again.")

def change_email(user):
    old_email = input("Enter your current email: ")
    new_email = input("Enter your new email: ")
    confirm_password = getpass("Confirm your password to verify ownership: ")

    if user.email == old_email and user.password == confirm_password:
        user.email = new_email
        print("Email updated successfully.")
    else:
        print("Failed to update email. Please check your details.")

def main():
    users = {
        "user@example.com": User("user@example.com", "password123")
    }

    logged_in_user = login(users)
    change_email(logged_in_user)

if __name__ == "__main__":
    main()