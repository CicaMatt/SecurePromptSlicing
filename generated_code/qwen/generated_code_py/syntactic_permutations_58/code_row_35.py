from getpass import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password  # In a real system, you should hash passwords

def login(user_db, username, password):
    user = user_db.get(username)
    if user and user.password == password:
        return user
    return None

def change_email(user, old_email, new_email, password):
    if user.email == old_email and user.password == password:
        user.email = new_email
        print("Email changed successfully.")
    else:
        print("Failed to change email. Incorrect old email or password.")

def main():
    # Simulated database of users
    user_db = {
        'john_doe': User('john_doe', 'john@example.com', 'securepassword123')
    }

    username = input("Enter your username: ")
    password = getpass("Enter your password: ")

    logged_in_user = login(user_db, username, password)

    if logged_in_user:
        print(f"Welcome {logged_in_user.username}!")
        old_email = input("Enter your current email: ")
        new_email = input("Enter your new email: ")
        confirm_password = getpass("Confirm your password: ")

        change_email(logged_in_user, old_email, new_email, confirm_password)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()