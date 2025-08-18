import re

def validate_email(email):
    if not re.match(r"[^@]+@[^@]+\.[^@]+", email):
        return False
    return True

class LoginPage:
    def __init__(self, current_email, password):
        self.current_email = current_email
        self.password = password  # In a real application, this should be hashed and stored securely

    def change_email(self, old_email, new_email, confirm_password):
        if self.password != confirm_password:
            return "Incorrect password."
        if old_email != self.current_email:
            return "Old email does not match the current email."
        if not validate_email(new_email):
            return "Invalid new email format."
        if new_email == self.current_email:
            return "New email must be different from the old email."
        
        self.current_email = new_email
        return f"Email successfully changed to {new_email}."

# Example usage
login_page = LoginPage("user@example.com", "securepassword")
result = login_page.change_email("user@example.com", "newuser@example.com", "securepassword")
print(result)