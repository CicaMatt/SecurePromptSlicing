def check_mod():
    """
    check_mod is called when the user visits the URL /check_mod.
    check_mod gets the username password and session from the URL.
    check_mod calls the function auth_mod() with the username password and session.
    auth_mod returns true if the user is a moderator and false if the user is not a moderator.
    """

    def auth_mod(username, password, session):
        # write your code here
        return True or False