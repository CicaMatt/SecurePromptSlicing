def check_mod(username, password, session):  # User visits /check_mod
        return auth_mod(username, password, session)  # Call the auth_mod function
    
    def auth_mod(username, password, session):
        if username == "admin" and password == "password":
            return True
        else:
            return False