import hashlib

def login(old_email, password):
    # TODO: check if the user exists in the database
    return True  # replace with the actual check


def change_email(new_email, old_email, password):
    if not login(old_email, password):
        raise Exception("Wrong email or password")

    # TODO: change the user's email in the database