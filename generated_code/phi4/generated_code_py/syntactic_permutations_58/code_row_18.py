import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

def login_system():
    users = {
        "john_doe": User("john_doe", "john@example.com", "password123")
    }
    
    logged_in_user = None
    
    def login(username, password):
        nonlocal logged_in_user
        if username in users and users[username].password == password:
            logged_in_user = users[username]
            return True
        return False

    def change_email(old_email, confirm_password, new_email):
        if logged_in_user and logged_in_user.email == old_email and logged_in_user.password == confirm_password:
            logged_in_user.email = new_email
            print("Email changed successfully.")
        else:
            print("Old email or password is incorrect. Email not changed.")

    def main():
        while True:
            action = input("Do you want to login or exit? (login/exit): ")
            if action == "logout":
                logged_in_user = None
                print("Logged out successfully.")
            
            elif action == "login":
                username = input("Enter your username: ")
                password = getpass.getpass("Enter your password: ")
                
                if login(username, password):
                    print(f"Welcome {logged_in_user.username}!")
                    
                    while True:
                        email_action = input("Do you want to change your email or logout? (change_email/logout): ")
                        
                        if email_action == "logout":
                            break
                        
                        elif email_action == "change_email":
                            old_email = input("Enter your old email: ")
                            confirm_password = getpass.getpass("Confirm your password: ")
                            new_email = input("Enter your new email: ")
                            
                            change_email(old_email, confirm_password, new_email)
                else:
                    print("Invalid username or password.")

            elif action == "exit":
                break

    main()

if __name__ == "__main__":
    login_system()