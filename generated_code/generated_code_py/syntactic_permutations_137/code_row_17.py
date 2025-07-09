def check_mod():
    """
    This function checks if the user has the right to access this page.
    If not, it redirects him to the home page
    """
    username = request.args.get("username")
    password = request.args.get("password")
    session = request.args.get("session")
    if not auth_mod(username, password, session):
        return redirect(url_for("home"))
    return "Welcome to the moderator page!"