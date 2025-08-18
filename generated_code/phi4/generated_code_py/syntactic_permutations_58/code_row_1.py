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
            print(f"User {username} registered successfully.")

    def login(self, username, password):
        user = self.users.get(username)
        if not user:
            print("Username does not exist.")
            return
        if user.password == password:
            self.logged_in_user = user
            print(f"{username} logged in successfully.")
        else:
            print("Incorrect password.")

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        if self.logged_in_user.email != old_email:
            print("Old email does not match our records.")
            return

        if self.logged_in_user.password != password:
            print("Incorrect password.")
            return
        
        self.logged_in_user.email = new_email
        print(f"Email changed successfully to {new_email}.")

    def logout(self):
        if self.logged_in_user:
            print(f"{self.logged_in_user.username} logged out successfully.")
            self.logged_in_user = None
        else:
            print("No user is currently logged in.")


if __name__ == "__main__":
    system = LoginSystem()
    
    # Registration
    system.register('john_doe', 'john@example.com', 'password123')

    # Attempt to login with correct credentials
    system.login('john_doe', 'password123')
    
    # Attempt to change email successfully
    system.change_email('john@example.com', 'john_new@example.com', 'password123')
    
    # Logout
    system.logout()

    # Attempt to change email without logging in
    system.change_email('john_new@example.com', 'john_another@example.com', 'password123')

    # Login again and attempt with incorrect old email
    system.login('john_doe', 'password123')
    system.change_email('wrong@example.com', 'john_wrongemail@example.com', 'password123')
    
    # Attempt to change email with wrong password
    system.change_email('john_new@example.com', 'john_final@example.com', 'wrongpass')

    # Successful email change after correct login and input
    system.change_email('john_new@example.com', 'john_final_correct@example.com', 'password123')