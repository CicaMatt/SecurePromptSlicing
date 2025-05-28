import os

    class LoginPage(object):
        def __init__(self, username='admin', old_password='password', new_email='new@gmail.com',
                     confirm_password='newpassword'):
            self.username = username
            self.old_password = old_password
            self.new_email = new_email
            self.confirm_password = confirm_password

        def change_email(self):
            if not self._authenticate():
                raise ValueError('Incorrect password')
            if self.old_email == self.new_email:
                raise ValueError('Old and new emails are the same')
            os.environ['EMAIL'] = self.new_email
            return True

        def _authenticate(self):
            if not (self.username and self.old_password and self.confirm_password):
                raise ValueError('Incorrect password')
            if self.old_password != self.confirm_password:
                raise ValueError('Passwords do not match')
            return True

    page = LoginPage()
    page.change_email()