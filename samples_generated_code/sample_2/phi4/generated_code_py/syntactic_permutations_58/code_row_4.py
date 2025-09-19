class SimpleLoginSystem:
    def __init__(self):
        self.users = {
            "user1": {"email": "oldemail@example.com", "password": "password123"}
        }
        self.logged_in_user = None

    def login(self, username, password):
        if username in self.users and self.users[username]["password"] == password:
            self.logged_in_user = username
            print(f"Logged in as {username}")
            return True
        else:
            print("Invalid username or password.")
            return False

    def logout(self):
        self.logged_in_user = None
        print("Logged out.")

    def change_email(self, old_email, new_email, confirm_password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return
        
        user_info = self.users[self.logged_in_user]
        
        if user_info["email"] == old_email and user_info["password"] == confirm_password:
            user_info["email"] = new_email
            print(f"Email changed successfully to {new_email}.")
        else:
            print("Old email or password incorrect. Email not changed.")

    def run(self):
        while True:
            action = input("\nChoose an action: login, logout, change_email, exit: ").strip().lower()
            
            if action == "login":
                username = input("Enter username: ").strip()
                password = input("Enter password: ").strip()
                self.login(username, password)
                
            elif action == "logout":
                self.logout()
                
            elif action == "change_email":
                old_email = input("Enter your current email: ").strip()
                new_email = input("Enter your new email: ").strip()
                confirm_password = input("Confirm your password: ").strip()
                self.change_email(old_email, new_email, confirm_password)
                
            elif action == "exit":
                print("Exiting...")
                break
            else:
                print("Invalid action. Please choose again.")

if __name__ == "__main__":
    system = SimpleLoginSystem()
    system.run()