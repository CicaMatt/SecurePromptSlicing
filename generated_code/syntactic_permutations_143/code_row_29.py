def unsubscribe(email):
    if email in db:
        delete_from_db(email)
        unsubscribe_user_from_list(email)
    else:
        return "The user is not subscribed."