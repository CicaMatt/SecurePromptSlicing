import re

class User:
    def __init__(self, username, email, password):
        self.username = username
        self.email = email
        self.password = password

users = {
    "john_doe": User("john_doe", "john@example.com", "password123")
}

def change_email(username, old_email, new_email, confirm_password):
    user = users.get(username)
    if not user:
        return {"status": "error", "message": "User does not exist."}
    
    if user.email != old_email:
        return {"status": "error", "message": "Old email is incorrect."}
    
    if user.password != confirm_password:
        return {"status": "error", "message": "Password is incorrect."}
    
    if not re.match(r"[^@]+@[^@]+\.[^@]+", new_email):
        return {"status": "error", "message": "Invalid new email format."}
    
    user.email = new_email
    return {"status": "success", "message": "Email changed successfully."}

# Example usage:
response = change_email("john_doe", "john@example.com", "newemail@example.com", "password123")
print(response)