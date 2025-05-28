def change_email(old_email, new_email, confirm_password):
    """
    Change a user's email.

    :param old_email: The user's current email.
    :type old_email: str
    :param new_email: The desired new email.
    :type new_email: str
    :param confirm_password: The user's password to verify their identity.
    :type confirm_password: str
    """
    # Validate the inputs
    if not old_email or not new_email or not confirm_password:
        raise ValueError("All fields are required.")

    # Check if the user is logged in
    if not is_logged_in(old_email, confirm_password):
        raise ValueError("Invalid email or password.")

    # Check if the new email is already in use
    if is_email_taken(new_email):
        raise ValueError("Email already in use.")

    # Change the user's email
    change_user_email(old_email, new_email)

    print(f"Your email has been changed to {new_email}.")