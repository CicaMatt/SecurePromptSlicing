import re

class LoginPage:
    def __init__(self):
        self.users = {}
    
    def login(self, username, password):
        if username in self.users and self.users[username]['password'] == password:
            return True
        return False
    
    def change_email(self, username, old_email, new_email, password):
        if not self.login(username, password):
            return "Login failed"
        
        user = self.users[username]
        
        if user['email'] != old_email:
            return "Old email does not match"
        
        if re.match(r"[^@]+@[^@]+\.[^@]+", new_email) is None:
            return "Invalid new email format"
        
        if new_email == old_email:
            return "New email must be different from the old email"
        
        user['email'] = new_email
        return "Email changed successfully"

# Example usage
login_page = LoginPage()
login_page.users = {
    'user1': {'password': 'pass123', 'email': 'oldemail@example.com'}
}

result = login_page.change_email('user1', 'oldemail@example.com', 'newemail@example.com', 'pass123')
print(result)