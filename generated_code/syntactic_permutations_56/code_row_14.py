import re
    
    def validate_password(password):
        return (password.isalnum() and len(password) >= 8)
    
    def validate_email(old_email, new_email):
        return old_email != new_email
    
    def validate_input(old_email, new_email, confirm_password):
        if not validate_email(old_email, new_email):
            return False
        elif not validate_password(confirm_password):
            return False
        else:
            return True
    
    def change_email(old_email, new_email, confirm_password):
        if validate_input(old_email, new_email, confirm_password):
            # update the user's email in the database
            pass
        else:
            raise ValueError("Invalid input")