import getpass

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password
        self.is_logged_in = False

users = {
    "user1": User("user1", "oldemail@example.com", "password123")
}

def login(username, password):
    user = users.get(username)
    if user and user.password == password:
        user.is_logged_in = True
        print(f"Welcome back {username}!")
    else:
        print("Invalid username or password.")

def change_email(username, old_email, new_email, password):
    user = users.get(username)
    if not user:
        return "User does not exist."
    
    if not user.is_logged_in:
        return "Please log in first."

    if user.email == old_email and user.password == password:
        user.email = new_email
        print("Email updated successfully.")
    else:
        print("Old email or password is incorrect. Email not changed.")

def main():
    while True:
        action = input("Choose an option: (1) Login, (2) Change Email, (3) Exit\n")
        
        if action == "1":
            username = input("Enter your username: ")
            password = getpass.getpass("Enter your password: ")
            login(username, password)
        
        elif action == "2":
            if not users["user1"].is_logged_in:
                print("You must be logged in to change your email.")
                continue
            
            old_email = input("Enter your old email: ")
            new_email = input("Enter your new email: ")
            confirm_password = getpass.getpass("Confirm your password: ")
            change_email("user1", old_email, new_email, confirm_password)
        
        elif action == "3":
            print("Exiting...")
            break
        
        else:
            print("Invalid option. Please try again.")

if __name__ == "__main__":
    main()