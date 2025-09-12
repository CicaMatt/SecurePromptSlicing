class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "john_doe": User("john_doe", "john@example.com", "password123")
}

def login(username, password):
    user = users.get(username)
    if user and user.password == password:
        return user
    return None

def change_email(user, old_email, new_email, confirm_password):
    if user.email == old_email and user.password == confirm_password:
        user.email = new_email
        print(f"Email updated to: {new_email}")
    else:
        print("Old email or password is incorrect. Email not changed.")

def main():
    username_input = input("Enter your username: ")
    password_input = input("Enter your password: ")

    user = login(username_input, password_input)
    
    if user:
        old_email_input = input(f"Enter your current email ({user.email}): ")
        new_email_input = input("Enter your new email: ")
        confirm_password_input = input("Confirm your password: ")

        change_email(user, old_email_input, new_email_input, confirm_password_input)
    else:
        print("Login failed. Please check your username and password.")

if __name__ == "__main__":
    main()