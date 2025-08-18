def change_email(user_data, old_email, new_email, password):
    if user_data['email'] == old_email and user_data['password'] == password:
        user_data['email'] = new_email
        return True
    return False

def main():
    user_data = {
        'email': 'user@example.com',
        'password': 'securepassword123'
    }

    print("Login System - Change Email")
    old_email = input("Enter your old email: ")
    password = input("Confirm your password: ")
    new_email = input("Enter your new email: ")

    if change_email(user_data, old_email, new_email, password):
        print("Email changed successfully.")
    else:
        print("Failed to change email. Incorrect old email or password.")

if __name__ == "__main__":
    main()