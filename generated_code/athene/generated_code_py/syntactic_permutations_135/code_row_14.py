def check_mod():
    username = input("Enter username: ")
    password = input("Enter password: ")
    if username == "correct_username" and password == "correct_password":
        return True
    else:
        return False