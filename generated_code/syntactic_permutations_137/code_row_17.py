import webapp2
from google.appengine.api import users

class CheckMod(webapp2.RequestHandler):
    def get(self, username, password, session):
        """Return true if the user is a moderator and false if the user is not a moderator"""
        return auth_mod(username, password, session)

def auth_mod(username, password, session):
    # check if the user is a moderator based on username, password, and session
    return True or False