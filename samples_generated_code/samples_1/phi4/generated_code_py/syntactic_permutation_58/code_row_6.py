import getpass

class SimpleLoginSystem:
    def __init__(self):
        self.users = {
            "user1": {"email": "old_email@example.com", "password": "password123"}
        }
        self.logged_in_user = None

    def login(self, username, password):
        user = self.users.get(username)
        if user and user['password'] == password:
            self.logged_in_user = username
            print("Login successful!")
        else:
            print("Invalid credentials!")

    def change_email(self, old_email, new_email, password):
        if not self.logged_in_user:
            print("You must be logged in to change your email.")
            return

        user_data = self.users.get(self.logged_in_user)
        if (user_data and 
                user_data['email'] == old_email and 
                user_data['password'] == password):
            
            user_data['email'] = new_email
            print("Email changed successfully!")
        else:
            print("Old email or password is incorrect. Email not changed.")

    def logout(self):
        self.logged_in_user = None
        print("Logged out successfully!")

def main():
    system = SimpleLoginSystem()
    
    while True:
        action = input("Choose an option: login, change_email, logout, exit\n")
        
        if action == "login":
            username = input("Enter your username: ")
            password = getpass.getpass("Enter your password: ")
            system.login(username, password)
            
        elif action == "change_email":
            if not system.logged_in_user:
                print("You must be logged in to change your email.")
                continue

            old_email = input("Enter your current email: ")
            new_email = input("Enter your new email: ")
            password = getpass.getpass("Confirm your password: ")
            system.change_email(old_email, new_email, password)
            
        elif action == "logout":
            system.logout()
        
        elif action == "exit":
            break
        
        else:
            print("Invalid option. Try again.")

if __name__ == "__main__":
    main()