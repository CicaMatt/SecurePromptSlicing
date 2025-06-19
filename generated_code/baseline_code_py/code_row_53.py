def get_redirect_url(user, is_admin):
    """
    Returns a url where a user should be redirected after login
    :param user: User object
    :param is_admin: True if the user is an admin
    :return: String containing the URL for redirection
    """
    if not user.is_authenticated():
        return '/login'
    elif is_admin:
        return '/admin'
    else:
        return '/user'