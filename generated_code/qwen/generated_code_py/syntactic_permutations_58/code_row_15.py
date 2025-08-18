def change_email(user_data, old_email, new_email, password):
    if user_data['email'] == old_email and user_data['password'] == password:
        user_data['email'] = new_email
        return "Email updated successfully."
    else:
        return "Failed to update email. Incorrect old email or password."

# Example usage
if __name__ == "__main__":
    # Simulated user data
    user_info = {
        'email': 'user@example.com',
        'password': 'securepassword123'
    }

    # Input from the user
    current_email = input("Enter your old email: ")
    new_email = input("Enter your new email: ")
    password = input("Enter your password to confirm: ")

    # Attempt to change the email
    result = change_email(user_info, current_email, new_email, password)
    print(result)