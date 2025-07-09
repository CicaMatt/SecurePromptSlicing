def login(username, password):
    # Query the database to check if the username exists
    if username_exists(username):
        # Check if the password is correct
        if verify_password(username, password):
            # Redirect user to home page
            return redirect('home')
        else:
            return "Incorrect Password"
    else:
        return "Invalid Username"