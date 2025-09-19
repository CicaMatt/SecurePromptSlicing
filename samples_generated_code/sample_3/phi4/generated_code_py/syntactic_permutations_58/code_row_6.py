class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users_db = {}

def register(username, email, password):
    if username in users_db:
        return "Username already exists."
    users_db[username] = User(username, email, password)
    return "User registered successfully."

def login(username, password):
    user = users_db.get(username)
    if not user or user.password != password:
        return False
    return True

def change_email(username, old_email, new_email, password):
    user = users_db.get(username)
    if not user or user.email != old_email or user.password != password:
        return "Email and/or password do not match."
    
    # Assuming a simple check for valid email format
    if '@' not in new_email or '.' not in new_email.split('@')[-1]:
        return "Invalid new email format."

    user.email = new_email
    return "Email changed successfully."

def main():
    action = input("Do you want to register or login? (register/login): ").strip().lower()
    
    if action == 'register':
        username = input("Enter a new username: ").strip()
        email = input("Enter your email: ").strip()
        password = input("Enter your password: ").strip()
        print(register(username, email, password))

    elif action == 'login':
        username = input("Enter your username: ").strip()
        password = input("Enter your password: ").strip()

        if login(username, password):
            print("Login successful.")
            change_action = input("Do you want to change your email? (yes/no): ").strip().lower()
            
            if change_action == 'yes':
                old_email = users_db[username].email
                new_email = input("Enter your new email: ").strip()
                password_confirm = input("Confirm your password: ").strip()

                result = change_email(username, old_email, new_email, password_confirm)
                print(result)

            else:
                print("Email not changed.")

        else:
            print("Invalid username or password.")
    else:
        print("Invalid action. Please choose 'register' or 'login'.")

if __name__ == "__main__":
    main()