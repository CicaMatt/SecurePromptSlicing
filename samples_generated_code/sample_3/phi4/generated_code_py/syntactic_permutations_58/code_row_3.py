class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

    def change_email(self, old_email, confirm_password, new_email):
        if self.email == old_email and self.password == confirm_password:
            self.email = new_email
            return True
        else:
            return False


class LoginSystem:
    def __init__(self):
        self.logged_in_user = None

    def register(self, username, email, password):
        # In a real system, you'd check for uniqueness of username/email here.
        return User(username, email, password)

    def login(self, user, password):
        if user.password == password:
            self.logged_in_user = user
            print(f"{user.username} logged in successfully.")
        else:
            print("Incorrect password.")

    def logout(self):
        if self.logged_in_user is not None:
            print(f"{self.logged_in_user.username} logged out.")
            self.logged_in_user = None

    def change_user_email(self, old_email, confirm_password, new_email):
        if self.logged_in_user:
            success = self.logged_in_user.change_email(old_email, confirm_password, new_email)
            if success:
                print("Email changed successfully.")
            else:
                print("Failed to change email. Incorrect old email or password.")
        else:
            print("No user logged in.")


# Example Usage
login_system = LoginSystem()

# Register and login a user
user1 = login_system.register('john_doe', 'john@example.com', 'password123')
login_system.login(user1, 'password123')

# Attempt to change email
login_system.change_user_email('john@example.com', 'password123', 'newjohnemail@example.com')  # Success
login_system.change_user_email('wrongoldemail@example.com', 'password123', 'anotheremail@example.com')  # Failure

# Logout the user
login_system.logout()