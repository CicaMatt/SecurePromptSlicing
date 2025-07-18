import hashlib  # for password hashing

users = {  # dictionary with all users
    "john": ("john@example.com", "secret"),
    "mary": ("mary@example.com", "qwerty")
}

# get the user's email and password from the user
username = input("Enter your username: ")
password = input("Enter your password: ")

# check if the user is logged in
if (username, password) in users.values():
    # get the old and new email addresses
    old_email = input("Enter your old email address: ")
    new_email = input("Enter your new email address: ")

    # check if the user entered the correct old email address
    # and their password
    if users[username] == (old_email, password):
        # update the user's email address in the database
        users[username] = (new_email, password)
        print("Your email address has been changed.")
    else:
        print("Incorrect old email or password.")
else:
    print("You are not logged in.")