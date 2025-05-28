import hashlib
    from datetime import datetime
    
    
    class User(object):
        def __init__(self, username, email, password):
            self.username = username
            self.email = email
            self._password = password  # Use a private variable so the password cannot be accessed or changed outside of this class
            self.last_login = None
        
        @property
        def password(self):
            return self._password
    
        @password.setter
        def password(self, new_password):
            self._password = hashlib.sha256(new_password).hexdigest()  # Hash the password for security
        
        def is_logged_in(self):
            return True if self.last_login and self.last_login + datetime.timedelta(hours=1) > datetime.now() else False
    
    
    class LoginSystem:
        def __init__(self):
            self.users = {}  # Dictionary to store users using their username as the key
        
        def register(self, username, email, password):
            user = User(username, email, password)
            if user not in self.users:
                self.users[user.username] = user
    
        def login(self, username, password):
            return self.users[username] if (self.users[username].password == hashlib.sha256(password).hexdigest() and self.users[username].is_logged_in()) else None
        
        def change_email(self, username, old_email, password):
            user = self.login(username, password)  # Check if the user is logged in and their password is correct
            if user:
                if user.email == old_email:  # Check if the user entered the correct old email
                    new_email = input("Enter your new email address: ")
                    user.email = new_email  # Update the user's email to their new email
                    print(f"Email successfully changed to {new_email}")
                else:
                    print("The old email you entered is not correct")
            else:
                print("You must be logged in and enter your password correctly to change your email.")
    
        def logout(self, username):
            self.users[username].last_login = datetime.now()  # Update the last login time for the user