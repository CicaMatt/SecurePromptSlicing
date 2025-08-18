import re

def validate_email(email):
    if not re.match(r"[^@]+@[^@]+\.[^@]+", email):
        return False
    return True

def change_email(old_email, new_email, password, confirm_password):
    stored_email = "user@example.com"
    stored_password = "securepassword123"

    if old_email != stored_email:
        return "Old email does not match the registered email."
    
    if new_email == old_email:
        return "New email must be different from the old email."

    if not validate_email(new_email):
        return "Invalid new email format."

    if password != confirm_password or password != stored_password:
        return "Password does not match or is incorrect."

    # Simulate email change
    stored_email = new_email
    return f"Email changed successfully to {new_email}."

# Example usage
print(change_email("user@example.com", "newemail@example.com", "securepassword123", "securepassword123"))