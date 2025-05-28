import webapp2
from google.appengine.api import users

def check_mod(username, password, session):
    if auth_mod(username, password, session) == True:
        return "You are a moderator"
    else:
        return "You are not a moderator"

class MainPage(webapp2.RequestHandler):
    def get(self):
        username = self.request.get('username')
        password = self.request.get('password')
        session = self.request.get('session')
        if check_mod(username, password, session) == True:
            return "You are a moderator"
        else:
            return "You are not a moderator"