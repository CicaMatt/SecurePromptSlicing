if email in db.email:
    return unsubscribe_email(email)
else:
    return 0