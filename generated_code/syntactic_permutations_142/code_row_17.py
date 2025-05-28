def unsubscribe(email_address):
    db = Database('database.db')
    user = db.get_user(email_address)

    if user is None:
        raise ValueError('User does not exist')

    user['subscribed'] = False
    db.update_user(user)