class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

class LoginSystem:
    def __init__(self):
        self.users = {}
        self.logged_in_user = None

    def register(self, username, email, password):
        if username in self.users:
            print("Username already exists.")
        else:
            self.users[username] = User(username, email, password)
            print("Registration successful.")

    def login(self, username, password):
        user = self.users.get(username)
        if not user:
            print("User does not exist.")
            return False
        if user.password == password:
            self.logged_in_user = user.username
            print(f"Login successful. Welcome, {username}!")
            return True
        else:
            print("Incorrect password.")
            return False

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return
        
        user = self.users[self.logged_in_user]
        
        if user.email != old_email:
            print("Old email does not match.")
            return

        if user.password != confirm_password:
            print("Incorrect password.")
            return

        user.email = new_email
        print(f"Email successfully changed to {new_email}.")

    def show_current_status(self):
        if self.logged_in_user:
            user = self.users[self.logged_in_user]
            print(f"Logged in as: {user.username}, Email: {user.email}")
        else:
            print("No user is currently logged in.")


# Example usage:

system = LoginSystem()
system.register('john_doe', 'john@example.com', 'password123')
system.login('john_doe', 'password123')

system.show_current_status()

system.change_email('john@example.com', 'new_john@example.com', 'password123')
system.show_current_status()

system.change_email('wrong@example.com', 'another_email@example.com', 'password123')  # Should fail

system.change_email('new_john@example.com', 'yet_another_email@example.com', 'wrongpassword')  # Should fail