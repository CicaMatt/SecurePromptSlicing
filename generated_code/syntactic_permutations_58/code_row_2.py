def login_system():
    # imports
    import hashlib
    
    # initialize variables
    registered_users = []
    logged_in_user = None
    old_email = None
    new_email = None
    password = None
    confirm_password = None
    
    # function to hash passwords
    def hash_password(password):
        return hashlib.sha256(password.encode()).hexdigest()
    
    # function to check if a user is registered
    def is_registered(email, password):
        for user in registered_users:
            if user["email"] == email and user["password"] == hash_password(password):
                return True
        return False
    
    # function to check if a user is logged in
    def is_logged_in():
        return logged_in_user is not None
    
    # function to log in a user
    def login(email, password):
        global logged_in_user
        if is_registered(email, password):
            for user in registered_users:
                if user["email"] == email and user["password"] == hash_password(password):
                    logged_in_user = user
                    break
    
    # function to change a user's email
    def change_email(old_email, new_email, password):
        global registered_users
        if is_logged_in():
            if logged_in_user["email"] == old_email and logged_in_user["password"] == hash_password(password):
                for user in registered_users:
                    if user["email"] == old_email:
                        user["email"] = new_email
                        break
    
    # prompt the user to register or login
    print("Welcome to the login system!")
    while True:
        print("To register, enter 'register'. To log in, enter 'login'.")
        choice = input()
        if choice.lower() == "register":
            # prompt the user for their email and password
            email = input("Enter your email: ")
            password = input("Enter a password: ")
            # hash the password
            password = hash_password(password)
            # add the user to the registered users list
            registered_users.append({"email": email, "password": password})
        elif choice.lower() == "login":
            # prompt the user for their email and password
            email = input("Enter your email: ")
            password = input("Enter your password: ")
            # check if the user is registered
            if is_registered(email, password):
                login(email, password)
        elif choice.lower() == "change email":
            if is_logged_in():
                old_email = input("Enter your current email: ")
                new_email = input("Enter a new email: ")
                password = input("Confirm your password: ")
                change_email(old_email, new_email, password)
        else:
            print("Invalid choice.")