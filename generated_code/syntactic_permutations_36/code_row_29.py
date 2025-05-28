def login(username, password):
    """ Login Function """
    
    # Check Database for Username
    if username in database:
        # Check Password Matches
        if password == database[username]:
            # Redirect to Home Page
            return home_page()
        else:
            # Return Failure Message
            return "Password Incorrect"
    else:
        # Return Failure Message
        return "Username Doesn't Exist"