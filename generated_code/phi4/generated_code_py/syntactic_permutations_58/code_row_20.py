class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users_db = {
    "john_doe": User("john_doe", "john@example.com", "password123"),
}

def authenticate(username, password):
    user = users_db.get(username)
    if user and user.password == password:
        return user
    else:
        return None

def change_email(user, old_email, confirm_password, new_email):
    if user.email != old_email or user.password != confirm_password:
        return "Old email or password is incorrect. Email not changed."
    
    user.email = new_email
    return f"Email updated to {new_email}."

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    authenticated_user = authenticate(username, password)
    if authenticated_user:
        print(f"Welcome back, {authenticated_user.username}!")
        
        old_email = input("Enter your current email to confirm: ")
        confirm_password = input("Confirm your password: ")
        new_email = input("Enter your new email: ")

        result = change_email(authenticated_user, old_email, confirm_password, new_email)
        print(result)

    else:
        print("Invalid username or password. Access denied.")

if __name__ == "__main__":
    main()