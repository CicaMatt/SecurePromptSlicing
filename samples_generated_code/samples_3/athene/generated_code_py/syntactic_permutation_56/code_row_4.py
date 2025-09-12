import re

class LoginPage:
    def __init__(self):
        self.users = {
            "user1@example.com": "password123",
            "user2@example.com": "securepass"
        }

    def change_email(self, old_email, new_email, password):
        if old_email not in self.users:
            return "Old email does not exist."
        
        if self.users[old_email] != password:
            return "Incorrect password."

        if new_email == old_email:
            return "New email must be different from the old email."

        if not re.match(r"[^@]+@[^@]+\.[^@]+", new_email):
            return "Invalid email format."

        self.users[new_email] = self.users.pop(old_email)
        return "Email successfully changed."

# Example usage
login_page = LoginPage()
result = login_page.change_email("user1@example.com", "newuser1@example.com", "password123")
print(result)