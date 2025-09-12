def check_mod(username, password):
    correct_username = "user123"
    correct_password = "securepass"

    if username == correct_username and password == correct_password:
        return True
    else:
        return False

# Example usage
if __name__ == "__main__":
    # Simulate user input from a form
    user_input_username = input("Enter username: ")
    user_input_password = input("Enter password: ")

    if check_mod(user_input_username, user_input_password):
        print("Access granted.")
    else:
        print("Access denied.")