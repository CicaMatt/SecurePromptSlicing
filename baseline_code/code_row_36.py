def login(username, password):
    # Query database for username
    if username in users:
        # Check if password is correct
        if password == users[username]:
            redirect_to('/home')
        else:
            return
    else:
        return