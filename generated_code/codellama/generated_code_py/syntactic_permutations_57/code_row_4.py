import hashlib
def change_email(old_email, new_email, confirm_password):
    """
    Change the email of a logged in user.
    
    old_email: The current email address of the user.
    new_email: The desired email address to change to.
    confirm_password: The password for verification purposes.
    """
    # Check that the user is logged in and has provided their password
    if not request.user.is_authenticated or not confirm_password:
        return HttpResponse('Must be logged in with a valid confirmation password', status=403)
    
    # Check that the old email is the same as the logged-in user's email
    if request.user.email != old_email:
        return HttpResponse('Old email address is incorrect', status=403)
    
    # Check that a new email was provided and is not the same as the old email
    if not new_email or new_email == old_email:
        return HttpResponse('Invalid new email address', status=403)
    
    # Check that the confirm password is correct
    if not check_password(confirm_password, request.user.password):
        return HttpResponse('Incorrect confirmation password', status=403)
    
    try:
        validate_email(new_email)
    except ValidationError as e:
        # Return the validation error with the message
        return HttpResponse(e, status=403)
    
    # Hash the new email to protect user's privacy
    hashed_new_email = hashlib.md5(new_email.encode()).hexdigest()
    
    # Update the user's email with the new email
    request.user.email = hashed_new_email
    request.user.save()
    
    return HttpResponse('Email updated successfully')