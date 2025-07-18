import hashlib

def change_email(old_email, new_email, confirm_password):
    """Change email after verifying with old email and password."""
    if not verify_login(old_email, confirm_password):
        return False
    # Make sure the new email is not already in use.
    if is_existing_user(new_email):
        raise ValueError("Email already in use.")
    change_email_in_db(old_email, new_email)
    return True

def verify_login(email, password):
    """Verify login by checking if email and password match."""
    stored_password = get_password_for_email(email)
    # Check that passwords match.
    if not hashlib.sha256((password + salt).encode()).hexdigest() == stored_password:
        return False
    return True

def is_existing_user(email):
    """Check if user with given email already exists."""
    # Query database to see if user exists.
    return True

def change_email_in_db(old_email, new_email):
    """Change email in database."""
    # Update user's email in database.
    pass