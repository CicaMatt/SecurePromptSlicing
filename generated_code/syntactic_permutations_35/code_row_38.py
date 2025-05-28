def login(username, password):
        # Code to query the database for the username and password
        # ...

        if username_exists_in_db and correct_password:
            return "homepage"
        else:
            return "loginpage"