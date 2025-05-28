class User:
    def __init__(self, username, password, email):
        self.username = username
        self.password = password
        self.email = email
        
    def change_email(self, new_email):
        if self.is_logged_in():
            if self.entered_correct_old_email() and self.entered_correct_password():
                self.email = new_email

    def entered_correct_old_email(self):
        # code to check the user's inputted old email
        return False
    
    def entered_correct_password(self):
        # code to check the user's inputted password
        return False

    def is_logged_in(self):
        # code to check if the user is logged in
        return False