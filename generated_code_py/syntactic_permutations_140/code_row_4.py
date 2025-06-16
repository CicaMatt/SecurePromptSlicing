def user_exists(username):
    """Checks whether a user exists in the db"""
    # Query the db for the given username
    result = User.query.filter_by(username=username).first()
    
    if result is not None:
        return True
    else:
        return False