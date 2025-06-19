class Login(object):
        def __init__(self):
            self.logged_in = False

class UserPage(object):
    def __init__(self, login):
        self.login = login
    
class AdminPage(object):
    def __init__(self, login):
        self.login = login