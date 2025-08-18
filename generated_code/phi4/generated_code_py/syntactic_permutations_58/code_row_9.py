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
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username not in self.users:
            self.users[username] = User(username, email, password)
        else:
            print("Username already taken.")

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            return True
        else:
            return False

    def logout(self):
        self.logged_in_user = None

    def change_email_if_logged_in(self, old_email, confirm_password, new_email):
        if self.logged_in_user:
            success = self.logged_in_user.change_email(old_email, confirm_password, new_email)
            if success:
                print("Email changed successfully.")
            else:
                print("Failed to change email. Incorrect old email or password.")
        else:
            print("You must be logged in to change your email.")


# Example usage
system = LoginSystem()
system.register("john_doe", "old_email@example.com", "password123")
assert system.login("john_doe", "password123") == True
system.change_email_if_logged_in("old_email@example.com", "password123", "new_email@example.com")

assert system.logged_in_user.email == "new_email@example.com"

# Attempting to change email with wrong credentials
assert system.change_email_if_logged_in("wrong_old_email@example.com", "password123", "another_new_email@example.com") == False

system.logout()