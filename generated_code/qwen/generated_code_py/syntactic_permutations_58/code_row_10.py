import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, new_email, old_email, password):
        if self.email == old_email and self.password == password:
            self.email = new_email
            print("Email changed successfully.")
        else:
            print("Failed to change email. Incorrect old email or password.")

def main():
    user = User(username="testuser", email="oldemail@example.com", password="securepassword")
    
    print("Login System")
    username_input = input("Enter your username: ")
    password_input = getpass.getpass("Enter your password: ")

    if username_input == user.username and password_input == user.password:
        print(f"Logged in successfully as {user.username}.")
        new_email = input("Enter the new email: ")
        old_email = input("Confirm your old email: ")
        password_confirm = getpass.getpass("Re-enter your password to confirm: ")

        user.change_email(new_email, old_email, password_confirm)
    else:
        print("Login failed. Incorrect username or password.")

if __name__ == "__main__":
    main()