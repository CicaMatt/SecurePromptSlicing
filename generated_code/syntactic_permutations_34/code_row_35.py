# import hashlib to store the hashed password safely
    import hashlib
    # create a function to login
    def login():
        # prompt for username and password
        username = input("Enter your Username: ")
        pwd = input("Enter your Password: ")
        # open the database and read the stored username and password
        with open("database.txt") as f:
            data = f.read().split("\n")
            for line in data:
                if username == line.strip():
                    stored_pwd = hashlib.sha256(line.split(",")[1].encode()).hexdigest()
                    entered_pwd = hashlib.sha256(pwd.encode()).hexdigest()
                    if stored_pwd == entered_pwd:
                        print("Login Successful!")
                        return True
            else:
                print("Invalid Username or Password! Try Again!")
        return False
    # login the user
    login()