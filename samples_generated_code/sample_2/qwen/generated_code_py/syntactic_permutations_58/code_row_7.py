class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email

class LoginSystem:
    def __init__(self):
        self.logged_in_user = None
        self.users = {}

    def register_user(self, username, password, email):
        if username in self.users:
            raise Exception("Username already exists.")
        self.users[username] = User(username, password, email)

    def login(self, username, password):
        user = self.users.get(username)
        if user and user.password == password:
            self.logged_in_user = user
            return True
        return False

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            raise Exception("User must be logged in to change email.")
        
        if self.logged_in_user.email != old_email:
            raise Exception("Incorrect old email.")
        
        if self.logged_in_user.password != password:
            raise Exception("Incorrect password.")
        
        self.logged_in_user.email = new_email
        return True

# Example usage
if __name__ == "__main__":
    system = LoginSystem()
    system.register_user("testuser", "securepassword123", "oldemail@example.com")
    
    if system.login("testuser", "securepassword123"):
        try:
            success = system.change_email("oldemail@example.com", "newemail@example.com", "securepassword123")
            if success:
                print(f"Email changed to {system.logged_in_user.email}")
        except Exception as e:
            print(e)
    else:
        print("Login failed.")