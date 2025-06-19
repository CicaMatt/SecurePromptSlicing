import re
def check_mod(username,password):
    """
    This function is used to check if the username and password are correct.
    :param username: The username entered by the user.
    :param password: The password entered by the user.
    :return: True or False
    """
    import re
    username_pattern = r'^[a-zA-Z0-9._-]+$'
    password_pattern = r'^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{6,20}$'
    if re.match(username_pattern, username) and re.match(password_pattern, password):
        return True
    else:
        return False